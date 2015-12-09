#include <opencv2/opencv.hpp>
#include <iostream>

void drawImage( cv::Mat &img, cv::Point leftTop, cv::Point rightDown )
{
    cv::rectangle( img,
                   leftTop,
                   rightDown,
                   CV_RGB(0,0,255), 3, 8, 0);
}

const std::string keys =
        "{help      |         | print this message   }"
        "{@source   |camera   | camera or video source(./video/test.avi)   }"
        "{feature   |hog      | feature selection of  hog or haar }"
        "{camera    |0        | camera index for prediction    }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Human Detection App v1.0.0");
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

    bool hogFlag = false, haarFlag = false;
    cv::CascadeClassifier haarCascade;

    cv::HOGDescriptor hogDetector( cv::Size(64, 128),
                                   cv::Size(16, 16),
                                   cv::Size(8, 8),
                                   cv::Size(8, 8),
                                   9,
                                   1,
                                   -1,
                                   cv::HOGDescriptor::L2Hys,
                                   0.2,
                                   true,
                                   cv::HOGDescriptor::DEFAULT_NLEVELS);

//    cv::HOGDescriptor hogDetector( cv::Size(48, 96),
//                                   cv::Size(16, 16),
//                                   cv::Size(8, 8),
//                                   cv::Size(8, 8),
//                                   9,
//                                   1,
//                                   -1,
//                                   cv::HOGDescriptor::L2Hys,
//                                   0.2,
//                                   true,
//                                   cv::HOGDescriptor::DEFAULT_NLEVELS);

    std::string feature = parser.get<std::string>("feature");

    if( feature == "hog" ){
        // cv::HOGDescriptor::getDefaultPeopleDetector() 64*128
        // cv::HOGDescriptor::getDaimlerPeopleDetector() 48*96
        hogDetector.setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector() );
//        hogDetector.setSVMDetector( cv::HOGDescriptor::getDaimlerPeopleDetector() );
        hogFlag = true;
        std::cout<<"human detection using HOG feature"<<std::endl;
    }else if( feature == "haar" ){
        std::string cascade_name = "./haarcascade_fullbody.xml";
        if( !haarCascade.load( cascade_name ) ){
            std::cout<<"load cascade file error"<<std::endl;
            return -1;
        }else{
            haarFlag = true;
            std::cout<<"human detection using Haar feature"<<std::endl;
        }
    }else{
    }

    while(1){
        cv::Mat frame, grayMat;
        std::vector<cv::Rect> result;
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        if( haarFlag ){
            cv::cvtColor( frame, grayMat, cv::COLOR_BGR2GRAY );
            haarCascade.detectMultiScale( grayMat, result, 1.2, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
        }

        if( hogFlag ){
            cv::Size winShiftSize = cv::Size( 8, 8 );//搜尋框移動位置
            cv::Size paddingSize = cv::Size( 32, 32 );//補滿邊界位置
            hogDetector.detectMultiScale( frame, result, 0, winShiftSize, paddingSize, 1.05, 2);
        }

        for( std::vector<cv::Rect>::const_iterator r = result.begin(); r != result.end(); r++ )
        {
            cv::Rect rect = *r;
            int left = cvRound( rect.x );
            int top = cvRound( rect.y );
            int right = cvRound( rect.x + rect.width-1 );
            int bottom = cvRound( rect.y + rect.height-1 );
            cv::rectangle( frame,
                           cvPoint( left, top ),
                           cvPoint( right, bottom ),
                           CV_RGB(0,0,255), 3, 8, 0);
        }

        char key = (char) cv::waitKey(33);
        if( key == 27 || key == 'ESC' ){
            break;
        }
        cv::imshow("frame", frame);
    }

    return 0;
}
