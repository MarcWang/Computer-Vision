#include <opencv2/opencv.hpp>
#include <iostream>


const std::string keys =
        "{help      |         | print this message   }"
        "{@source   |camera   | camera or video source(./video/test.avi)   }"
        "{camera    |0        | camera index for prediction    }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Camera App v1.0.0");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::VideoCapture cap;
    std::string mediaSrc = parser.get<std::string>(0);
    if( mediaSrc == "camera" ){
        int camIdx = parser.get<int>("camera");
        cap.open("rtsp://root:pass@192.168.10.237:554/axis-media/media.amp");
    }else{
        cap.open(mediaSrc);
    }

    while(1){
        cv::Mat frame;
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        char key = (char) cv::waitKey(50);
        if( key == 27 || key == 'ESC' ){
            break;
        }
        cv::imshow("frame", frame);
    }

    return 0;
}
