#include <opencv2/opencv.hpp>
#include <iostream>
#include "HOGExtractor.h"
#include "SVMProcess.h"

//https://github.com/tronkko/dirent
#include <dirent.h>

#define OBJECT_SIZE 60

void drawImage( cv::Mat &img, cv::Point leftTop, cv::Point rightDown )
{
    cv::rectangle( img,
                   leftTop,
                   rightDown,
                   CV_RGB(0,0,255), 3, 8, 0);
}

std::vector<std::string> listFile( std::string path)
{
    std::vector<std::string> list;
    DIR *pDIR;
    struct dirent *entry;
    if( pDIR = opendir(path.c_str()) ){
        while(entry = readdir(pDIR)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                std::string name = path;
                name.append("/");
                name.append(entry->d_name);
                list.push_back(name);
            }
        }
        closedir(pDIR);
    }
    return list;
}

const std::string keys =
        "{help      |                   | print this message   }"
        "{@source   |camera             | camera or video source(./video/test.avi)   }"
        "{@action   |2                  | 0 = only training , 1 = only prediction , 2 = both training and prediction  }"
        "{negPath   |./data/negative    | the folder path of negative images for train }"
        "{posPath   |./data/positive    | the folder path of positive images for train }"
        "{camera    |0                  | camera index for prediction    }"
        ;

int main( int argc, char *argv[] )
{

    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Feature extraction App v1.0.0");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    std::vector<std::string> negDataList;
    std::vector<std::string> posDataList;
    cv::VideoCapture cap;

    std::string mediaSrc = parser.get<std::string>(0);
    if( mediaSrc == "camera" ){
        int camIdx = parser.get<int>("camera");
        cap.open(camIdx);
    }else{
        cap.open(mediaSrc);
    }

    int act = parser.get<int>(1);

    if( act == 2 ){

    }


    std::string negPath = parser.get<std::string>("negPath");
    std::cout<<"load negative images from data folder"<<std::endl;
    std::cout<<negPath<<std::endl;
    negDataList = listFile(negPath);
    std::cout<<"total negative images = "<<negDataList.size()<<std::endl;

    std::string posPath = parser.get<std::string>("posPath");
    std::cout<<"load positive images from data folder"<<std::endl;
    std::cout<<posPath<<std::endl;
    posDataList = listFile(posPath);
    std::cout<<"total positive images = "<<posDataList.size()<<std::endl;



    /*************************************************************************/
    /*******************************train begin*******************************/
    /*************************************************************************/

    HOGExtractor hogHandler;
    HOGParams params;
    hogHandler.initialize( params, OBJECT_SIZE, OBJECT_SIZE);
    SVMProcess svmHandler;

    for( std::vector<std::string>::const_iterator r = negDataList.begin(); r != negDataList.end(); r++ )
    {
        std::string name = *r;
        cv::Mat grayMat, resizeMat;
        grayMat = cv::imread(name, 0 );
        cv::resize( grayMat, resizeMat, cv::Size( OBJECT_SIZE, OBJECT_SIZE ));

        cv::Mat resMat;
        hogHandler.extract( resizeMat, resMat );
        svmHandler.pushTrainData( resMat, -1);
    }

    for( std::vector<std::string>::const_iterator r = posDataList.begin(); r != posDataList.end(); r++ )
    {
        std::string name = *r;
        cv::Mat grayMat, resizeMat;
        grayMat = cv::imread(name, 0 );
        cv::resize( grayMat, resizeMat, cv::Size( OBJECT_SIZE, OBJECT_SIZE ));

        cv::Mat resMat;
        hogHandler.extract( resizeMat, resMat );
        svmHandler.pushTrainData( resMat, 1);
    }

    svmHandler.train();
    /*************************************************************************/
    /********************************train end********************************/
    /*************************************************************************/

    std::vector<float> detector = svmHandler.outputDetector();
    hogHandler.setSVM("hog.txt");
//    hogHandler.setSVM(detector);

    while(1){
        cv::Mat frame;
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        cv::Mat grayMat;
        cv::cvtColor( frame, grayMat, cv::COLOR_BGR2GRAY );

        std::vector<cv::Rect> result;
        hogHandler.detect( grayMat, result );
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
        if( key == '27' ){
            break;
        }
        cv::imshow("frame", frame);
    }

    return 0;
}
