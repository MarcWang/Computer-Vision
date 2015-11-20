#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

//使用Mat.ptr取出位址，再用[]方式取值
cv::Mat matControl_1( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;

    for( int j = 0; j < nRows; j++ ) {
        uchar* srcData = srcMat.ptr<uchar>(j);
        uchar* dstData = dstMat.ptr<uchar>(j);
        for( int i = 0; i < nCols; i++) {
            dstData[nChannels*i + 2]= srcData[nChannels*i + 2];
            dstData[nChannels*i + 1]= srcData[nChannels*i + 1];
            dstData[nChannels*i + 0]= srcData[nChannels*i + 0];
        }
    }

    return dstMat;
}


//使用Mat.ptr取出位址，再用*方式取值
cv::Mat matControl_2( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;

    for( int j = 0; j < nRows; j++ ){
        uchar* srcData= srcMat.ptr<uchar>(j);
        uchar* dstData = dstMat.ptr<uchar>(j);
        for( int i = 0; i < nCols; i++ ){
            *dstData++ = *srcData++;
        }
    }

    return dstMat;
}


//直接指標取值
cv::Mat matControl_3( cv::Mat srcMat )
{

    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;
    int nStep = srcMat.step;

    uchar* srcData= srcMat.data;
    uchar* dstData = dstMat.data;
    for( int j = 0; j < nRows; j++ ){
        for( int i = 0; i < nCols; i++ ) {
            *(dstData+i) = *(srcData+i);
        }
        srcData += nStep;
        dstData += nStep;
    }

    return dstMat;
}

//座標訪問
cv::Mat matControl_4( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );

    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;
    for( int j = 0; j < nRows; j++ ){
        uchar* dstData = dstMat.ptr<uchar>(j);
        for( int i = 0; i < nCols; i++ ){
            cv::Vec3b srcPixel = srcMat.at<cv::Vec3b>(j, i);
            *dstData++ = srcPixel[0];
            *dstData++ = srcPixel[1];
            *dstData++ = srcPixel[2];
        }
    }

    return dstMat;
}

//使用Mat.isContinuous()判斷是否為連續影像，優化迴圈
cv::Mat matControl_5( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;

    if( srcMat.isContinuous()){
        nCols *= nRows;
        nRows = 1;
    }

    for( int j = 0; j < nRows; j++ ){
        uchar* srcData= srcMat.ptr<uchar>(j);
        uchar* dstData = dstMat.ptr<uchar>(j);
        for( int i = 0; i < nCols; i++ ){
            *dstData++ = *srcData++;
        }
    }

    return dstMat;
}

//使用iterator訪問取值
cv::Mat matControl_6( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.cols, srcMat.rows, srcMat.type() );
    cv::Mat_<cv::Vec3b>::iterator it = srcMat.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = srcMat.end<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator dstIter = dstMat.begin<cv::Vec3b>();

    for ( ; it!= itend; ++it, ++dstIter) {
        (*dstIter)[0]= (*it)[0];
        (*dstIter)[1]= (*it)[1];
        (*dstIter)[2]= (*it)[2];
    }

    return dstMat;
}


int main()
{

  Mat img;
  img = imread( "lena.jpg", 1 );
  int64 start = 0, end = 0;

  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
      matControl_1( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
       matControl_2( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
      matControl_3( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
      matControl_4( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
      matControl_5( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  start = cv::getTickCount();
  for( int i = 0; i < 1000; i++){
      matControl_6( img );
  }
  end = cv::getTickCount();
  std::cout<<"Process Time = "<<(end-start)/cv::getTickFrequency()<<"s"<<std::endl;


  cv::imshow("src", img);
  cv::waitKey(0);

}
