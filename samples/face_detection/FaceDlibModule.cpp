#include "FaceDlibModule.h"

FaceDlibModule::FaceDlibModule()
{

}

FaceDlibModule::~FaceDlibModule()
{

}

MResult FaceDlibModule::initialize()
{
    MResult res = MResult::M_ERROR;
    detector = dlib::get_frontal_face_detector();
//    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

    res = MResult::M_OK;
    return res;
}

void *FaceDlibModule::createHandle()
{
    return NULL;
}

int FaceDlibModule::deleteHandle(void *handle)
{
    return 0;
}

MResult FaceDlibModule::detection(cv::Mat srcMat, MFaceResult &result)
{
    MResult res = MResult::M_ERROR;

    dlib::cv_image<dlib::bgr_pixel> cimg(srcMat);
    std::vector<dlib::rectangle> dlibFaces;
    dlibFaces = detector(cimg);

    int count = 0;
    for( std::vector<dlib::rectangle>::const_iterator r = dlibFaces.begin(); r != dlibFaces.end(); r++, count++ )
    {
        dlib::rectangle rect = *r;
        MFaceInfo info;
        info.rect.x = rect.left();
        info.rect.y = rect.top();
        info.rect.width = rect.width();
        info.rect.height = rect.height();
        result.infos.push_back( info );
    }
    result.counts = count;


    //            std::vector<dlib::full_object_detection> shapes;
    //            for (unsigned long i = 0; i < dlibFaces.size(); ++i)
    //                shapes.push_back(pose_model(cimg, dlibFaces[i]));
    //            win.add_overlay(dlib::render_face_detections(shapes));

    return res;
}

