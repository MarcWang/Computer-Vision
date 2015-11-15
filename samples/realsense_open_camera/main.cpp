#include <pxcsensemanager.h>
#include <pxcsession.h>
#include <pxccapturemanager.h>

#include <ImageFormatConverter.h>
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

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

    psm->EnableStream( PXCCapture::STREAM_TYPE_COLOR, WIDTH, HEIGHT);
    psm->EnableStream( PXCCapture::STREAM_TYPE_DEPTH, WIDTH, HEIGHT);

    // Set the coordinate system
    PXCSession *session = psm->QuerySession();
    session->SetCoordinateSystem( PXCSession::COORDINATE_SYSTEM_REAR_OPENCV );

    if( psm->Init() != PXC_STATUS_NO_ERROR ){
        std::cout<<"Unable to Init the PXCSenseManager"<<std::endl;
        return;
    }

    ImageFormatConverter *converter = new ImageFormatConverter();
    if( converter == NULL ){
        return;
    }

    PXCImage *colorIm, *depthIm;
    cv::Mat colorMat, depthMat;
    while(true){
        if( psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR ){
            break;
        }
        PXCCapture::Sample *sample = psm->QuerySample();
        if( sample ){
            if( sample->color ){
                colorIm = sample->color;
                colorMat = converter->convertPXCImageToOpenCVMat( colorIm, ImageFormatConverter::ImageFormat::STREAM_TYPE_COLOR );
            }
            if( sample->depth ){
                depthIm = sample->depth;
                depthMat = converter->convertPXCImageToOpenCVMat( depthIm, ImageFormatConverter::ImageFormat::STREAM_TYPE_DEPTH );
            }

            cv::imshow("Color Image on OpenCV Format", colorMat);
            cv::imshow("Depth Image on OpenCV Format", depthMat);
            cv::waitKey(1);
        }
        psm->ReleaseFrame();
    }
    psm->Release();
}
