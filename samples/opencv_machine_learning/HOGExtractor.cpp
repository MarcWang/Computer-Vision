#include "HOGExtractor.h"
#include <iostream>
#include <fstream>


HOGParams::HOGParams()
{
    blockSize       = cv::Size( 20, 20 );
    blockStrideSize = cv::Size( 10, 10 );
    cellSize        = cv::Size( 5, 5 );
    bins            = 9;
}



HOGExtractor::HOGExtractor()
{
    //一個Cell有bins個方向，共bins維
    //一個Block有16個Cells((20/5)*(20/5))，共144維
    //一個Window有25個Blocks(((60-20)/10+1)*((60-20)/10+1))，共3600維
    _hog        = NULL;

}

HOGExtractor::~HOGExtractor()
{
    if( _hog != NULL ){
        delete _hog;
    }
}

void HOGExtractor::initialize( HOGParams params, int width, int height )
{
    _winSize = cv::Size( width, height );
    _params  = params;
    _hog     = new cv::HOGDescriptor( _winSize, _params.blockSize, _params.blockStrideSize, _params.cellSize, _params.bins );
}

void HOGExtractor::setSVM(const char *path)
{
    std::vector<float> x;
    std::ifstream fileIn( path, std::ios::in);
    float val = 0.0f;
    while(!fileIn.eof())
    {
        fileIn>>val;
        x.push_back(val);
    }
    x.pop_back();
    fileIn.close();
    _hog->setSVMDetector( x );
}

void HOGExtractor::setSVM(std::vector<float> detector)
{
    _hog->setSVMDetector( detector );
}

void HOGExtractor::extract( cv::Mat frame, cv::Mat &resMat )
{
    if( _hog == NULL ){
        return;
    }

    if( _winSize.height != frame.rows || _winSize.width != frame.cols ){
        return;
    }

    cv::Size winShiftSize = cv::Size( 10, 10 );//搜尋框移動位置
    cv::Size paddingSize = cv::Size( 0, 0 );//補滿邊界位置
    std::vector<float> descriptors;
    _hog->compute( frame, descriptors, winShiftSize, paddingSize);//調用計算函數

    int dims = descriptors.size();

    resMat.release();
    resMat = cv::Mat(1, dims, CV_32FC1);
    float* data = resMat.ptr<float>(0);
    for( int j = 0; j < dims; j++){
        data[j]= descriptors[j];
    }
}

void HOGExtractor::detect(cv::Mat frame, std::vector<cv::Rect> &result)
{
    cv::Size winShiftSize = cv::Size( 20, 20 );//搜尋框移動位置
    cv::Size paddingSize = cv::Size( 0, 0 );//補滿邊界位置
    _hog->detectMultiScale( frame, result, 0, winShiftSize, paddingSize, 1.2, 2);
}


