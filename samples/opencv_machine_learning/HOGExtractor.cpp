#include "HOGExtractor.h"
#include <iostream>



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

    std::cout<<"Dims = "<<dims<<std::endl;

    resMat.release();
    resMat = cv::Mat(1, dims, CV_32FC1);
    float* data = resMat.ptr<float>(0);
    for( int j = 0; j < dims; j++){
        data[j]= descriptors[j];
    }
}


