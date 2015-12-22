#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>


const std::string keys =
        "{help      |         | print this message   }"
        "{@source   |camera   | camera or video source(./video/test.avi)   }"
        "{camera    |0        | camera index for prediction    }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("GPU VS CPU App v1.0.0");
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

    std::cout << "Have OpenCL?: " << cv::ocl::haveOpenCL() << std::endl;
    cv::ocl::setUseOpenCL(true);

    while(1){
        cv::UMat frame, hsvMat, resizeMat;
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        double t = (double)cv::getTickCount();

        cv::resize(frame, resizeMat, frame.size()*2);
        cv::cvtColor(resizeMat, hsvMat, cv::COLOR_RGB2HSV);
        t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
        std::cout << "Times passed in seconds: " << t << std::endl;

        char key = (char) cv::waitKey(33);
        if( key == 27 || key == 'ESC' ){
            break;
        }
        cv::imshow("frame", frame);
    }

    return 0;
}
