#ifndef IFACECOREMODULE_H
#define IFACECOREMODULE_H
#include <common.h>
#include <iostream>
#include <opencv/include/opencv2/opencv.hpp>

enum MResult {
    M_OK = 0,
    M_ERROR = -1
};


struct LIB_DECL MFaceInfo
{
    MFaceInfo(){

    }
    cv::Rect rect;
};

struct LIB_DECL MFaceResult
{
    int counts;
    std::vector<MFaceInfo> infos;
};


class LIB_DECL IFaceCoreModule
{
public:
    IFaceCoreModule();
    virtual ~IFaceCoreModule();
    virtual void* createHandle() = 0;
    virtual int deleteHandle( void* handle ) = 0;
    virtual MResult initialize() = 0;
    virtual MResult detection( cv::Mat srcMat, MFaceResult &result ) = 0;
};

#endif // IFACECOREMODULE_H
