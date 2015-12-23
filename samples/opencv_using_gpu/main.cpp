#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>


const std::string keys =
        "{help      |                   | print this message   }"
        "{@source   |./video/test.avi   | camera or video source(./video/test.avi)   }"
        "{camera    |0                  | camera index for prediction    }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("OpenCL App v1.0.0");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::VideoCapture cap;
    std::string mediaSrc = parser.get<std::string>(0);
    if( mediaSrc == "camera" ){
        int camIdx = parser.get<int>("camera");
        cap.open(camIdx);
    }else{
        cap.open(mediaSrc);
    }

    if( !cv::ocl::haveOpenCL() ){
        std::cout << "OpenCL is not avaiable..." << std::endl;
        return -1;
    }
    cv::ocl::Context context;
    if( !context.create(cv::ocl::Device::TYPE_GPU) ){
        std::cout << "Failed creating the context..." << std::endl;
        return -1;
    }

    std::cout << context.ndevices() << " GPU devices are detected." << std::endl;
    for (int i = 0; i < (int)context.ndevices(); i++){
        cv::ocl::Device device = context.device(i);
        std::cout << "name                 : " << device.name() << std::endl;
        std::cout << "available            : " << device.available() << std::endl;
        std::cout << "imageSupport         : " << device.imageSupport() << std::endl;
        std::cout << "OpenCL_C_Version     : " << device.OpenCL_C_Version() << std::endl;
        std::cout << std::endl;
    }


    cv::ocl::Device(context.device(0));
    const cv::ocl::Device &dev = cv::ocl::Device::getDefault();
    int max_wg_size = (int)dev.maxWorkGroupSize();
    std::cout << "GPU Memory Size : " << max_wg_size << std::endl;
    bool useGPU = true;

    int count = 0;
    double t = (double)cv::getTickCount();
    while(1){

        cv::Mat frame;
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        if(useGPU){
            cv::UMat uFrame, uGrayMat, uCannyMat;
            uFrame = frame.getUMat( cv::ACCESS_READ, cv::USAGE_ALLOCATE_DEVICE_MEMORY );
            cv::cvtColor(uFrame, uGrayMat, cv::COLOR_BGR2GRAY);
            cv::Canny( uGrayMat, uCannyMat, 50, 150, 3 );

            std::cout << "GPU - key frame : "<< count << std::endl;
        }else{
            cv::Mat grayMat, cannyMat;
            cv::cvtColor(frame, grayMat, cv::COLOR_BGR2GRAY);
            cv::Canny( grayMat, cannyMat, 50, 150, 3 );

            std::cout << "CPU - key frame : "<< count << std::endl;
        }


        char key = (char) cv::waitKey(5);
        if( key == 27 || key == 'ESC' ){
            break;
        }
        cv::imshow("frame", frame);
        count++;

    }
    t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
    std::cout << "Times passed in seconds: " << t << std::endl;

    return 0;
}
