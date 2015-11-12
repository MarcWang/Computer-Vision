#ifndef FACEDLIBMODULE_H
#define FACEDLIBMODULE_H
#include "AbstractFaceCoreModule.h"
#include <dlib/include/image_processing/frontal_face_detector.h>
#include <dlib/include/image_processing/render_face_detections.h>
#include <dlib/include/image_processing.h>
#include <dlib/include/opencv.h>

class FaceDlibModule : public AbstractFaceCoreModule
{
public:
    FaceDlibModule();
    virtual ~FaceDlibModule();
    virtual MResult initialize();
    virtual void* createHandle();
    virtual int deleteHandle( void* handle );
    virtual MResult detection( cv::Mat srcMat, MFaceResult &result );
private:
    dlib::frontal_face_detector detector;
    dlib::shape_predictor pose_model;
};

#endif // FACEDLIBMODULE_H
