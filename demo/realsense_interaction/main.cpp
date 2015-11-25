#include <pxcsensemanager.h>
#include <MediaResource.h>
#include <FaceCoreModule.h>
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

void drawFaceInfo( cv::Mat img, MFaceInfo info )
{
    PXCRectI32 rect = info.rect;
    int id = (int)info.id;
    cv::rectangle(
        img,
        cv::Rect(rect.x, rect.y, rect.w, rect.h),
        cv::Scalar(0, 0, 255)
    );

    std::stringstream convert;
    convert << id;
    std::string str = convert.str();
    cv::putText( img, cv::String(str), cv::Point(rect.x, rect.y), 3, 1, cv::Scalar(0, 255, 0), 1, 8, 0);

    int length = MAX_LANDMARK;
    for( int p = 0; p < length; p++ ){
        PXCPointF32 point = info.points[p].image;
        cv::circle( img, cv::Point((int)point.x, (int)point.y), 3, cv::Scalar(0, 255, 0), 1, 8, 0);
    }
}

void main()
{
    PXCSenseManager *psm = NULL;
    psm = PXCSenseManager::CreateInstance();
    if ( psm == NULL ){
        std::cout<<"Unabel to create the PXCSenseManager"<<std::endl;
        return;
    }

    std::cout<<"OpenCV Library Version:"<<CV_VERSION<<std::endl;

    PXCSession::ImplVersion version = psm->QuerySession()->QueryVersion();
    std::cout<<"RealSense SDK Version:"<<version.major<<"."<<version.minor<<std::endl;

    MFaceCoreModule *faceHandler = new MFaceCoreModule( psm );
    if( faceHandler == NULL ){
        return;
    }
    faceHandler->initialize();

    MediaResource *capture = new MediaResource();
    if( capture == NULL ){
        return;
    }
    capture->initialize( psm, 640, 480 );

    if( psm->Init() != PXC_STATUS_NO_ERROR ){
        std::cout<<"Unable to Init the PXCSenseManager"<<std::endl;
        return;
    }

    capture->start();


//            MFaceResult result;
//            faceHandler->detect( result );
//            int counts = result.getFaceCount();
//            for( int i = 0; i < counts; i++ ){
//                MFaceInfo info = result.getFaceInfo(i);
//                if( info.rect.w > 200 ){
//                    std::cout<<"Open"<<std::endl;
//                }else{
//                    std::cout<<"Close"<<std::endl;
//                }
////                drawFaceInfo( colorMat, info );
//            }
//            cv::imshow("Color Image on OpenCV Format", colorMat);
//            cv::waitKey(1);



    while(1){
        QThread::sleep(1);
    }
    delete faceHandler;
    psm->Release();
}
