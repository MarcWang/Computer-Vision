#include "FaceOpenCVModule.h"


FaceOpenCVModule::FaceOpenCVModule()
{

}

FaceOpenCVModule::~FaceOpenCVModule()
{

}

MResult FaceOpenCVModule::initialize()
{
    MResult res = MResult::M_ERROR;

    std::string cascadeName = "haarcascade_frontalface_alt.xml";
    if( !cascade.load( cascadeName ) ){
        res = MResult::M_ERROR;
        return res;
    }

    res = MResult::M_OK;
    return res;
}

void *FaceOpenCVModule::createHandle()
{
    return NULL;
}

int FaceOpenCVModule::deleteHandle(void *handle)
{
    return 0;
}

MResult FaceOpenCVModule::detection( cv::Mat srcMat, MFaceResult &result )
{
    MResult res = MResult::M_ERROR;

    std::vector<cv::Rect> faces;
    cv::Mat gray;
    cv::cvtColor( srcMat, gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( gray, gray );
    cascade.detectMultiScale( gray,
                              faces,
                              1.1,
                              3,
                              cv::CASCADE_SCALE_IMAGE,
                              cv::Size(80, 80) );

    int count = 0;
    for( std::vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, count++)
    {
        cv::Rect rect = *r;
        MFaceInfo info;
        info.rect = rect;
        result.infos.push_back( info );
    }
    result.counts = count;

    return res;
}

