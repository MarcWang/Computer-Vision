#ifndef FACEOPENCVMODULE_H
#define FACEOPENCVMODULE_H
#include "AbstractFaceCoreModule.h"

class FaceOpenCVModule : public AbstractFaceCoreModule
{
public:
    FaceOpenCVModule();
    virtual ~FaceOpenCVModule();
    virtual MResult initialize();
    virtual void* createHandle();
    virtual int deleteHandle( void* handle );
    virtual MResult detection( cv::Mat srcMat, MFaceResult &result );
private:
    cv::CascadeClassifier cascade;
};

#endif // FACEOPENCVMODULE_H
