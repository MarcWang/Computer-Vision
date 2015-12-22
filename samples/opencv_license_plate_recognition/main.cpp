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

    cv::CascadeClassifier haarCascade;
    std::string cascade_name = "./haarcascade_russian_plate_number.xml";
//    std::string cascade_name = "./haarcascade_licence_plate_rus_16stages.xml";
    if( !haarCascade.load( cascade_name ) ){
        std::cout<<"load cascade file error"<<std::endl;
        return -1;
    }else{

    }


    while(1){
        cv::Mat frame, grayMat;
        std::vector<cv::Rect> result;
        cap >> frame;
        if( frame.empty() ){
            break;
        }


        cv::cvtColor( frame, grayMat, cv::COLOR_BGR2GRAY );
        haarCascade.detectMultiScale( grayMat, result, 1.2, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );


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
