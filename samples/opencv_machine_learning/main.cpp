#include <opencv2/opencv.hpp>
#include <iostream>
#include "HOGExtractor.h"
#include "SVMProcess.h"

void main()
{

    cv::Mat srcMat, grayMat;
    srcMat = cv::imread( "lena.jpg", 1 );
    cv::cvtColor( srcMat, grayMat, cv::COLOR_BGR2GRAY );

    cv::Mat sobelXMat, sobelYMat, sobelModifyXMat, sobelModifyYMat, sobelMat;
    cv::Sobel( grayMat, sobelXMat, CV_16S, 1, 0, 3);
    cv::convertScaleAbs( sobelXMat, sobelModifyXMat );
    cv::Sobel( grayMat, sobelYMat, CV_16S, 0, 1, 3);
    cv::convertScaleAbs( sobelYMat, sobelModifyYMat );

    cv::addWeighted( sobelModifyXMat, 0.5, sobelModifyYMat, 0.5, 0, sobelMat );

    cv::Mat resizeMat;
    cv::resize( sobelMat, resizeMat, cv::Size( 60, 60 ));

    HOGExtractor process;
    HOGParams params;
    process.initialize( params, 60, 60);

    cv::Mat resMat;
    process.extract( resizeMat, resMat );

    SVMProcess svm;


    cv::imshow("srcMat", srcMat);
    cv::imshow("grayMat", grayMat);
    cv::imshow("sobelMat", sobelMat);
    cv::imshow("resizeMat", resizeMat);

    cv::waitKey(0);

}
