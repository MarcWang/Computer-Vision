#include "MediaResource.h"

#include <iostream>

MediaResource::MediaResource()
{
    _captureState = false;
    _converter = NULL;
}

MediaResource::~MediaResource()
{
    if( _converter != NULL ){
        delete _converter;
    }
}

void MediaResource::initialize(PXCSenseManager *senseManager, int width, int height)
{
    if ( senseManager == NULL ){
//        std::cout<<"Load PXCSenseManager Error"<<std::endl;
        return;
    }
    _senseManager = senseManager;
    pxcF32 _width = static_cast<pxcF32>(width);
    pxcF32 _height = static_cast<pxcF32>(height);
    _senseManager->EnableStream( PXCCapture::STREAM_TYPE_COLOR, _width, _height);

    PXCSession *session = _senseManager->QuerySession();
    session->SetCoordinateSystem( PXCSession::COORDINATE_SYSTEM_REAR_OPENCV );

    _converter = new ImageFormatConverter();
    if( _converter == NULL ){
        return;
    }
}

void MediaResource::stop()
{
    _captureState = false;
}

void MediaResource::run()
{
    _captureState = true;
    while( _captureState ){
        QThread::msleep(30);
        if( _senseManager->AcquireFrame(true) < PXC_STATUS_NO_ERROR ){
            break;
        }
        std::cout<<"capture image"<<std::endl;

        PXCCapture::Sample *sample = _senseManager->QuerySample();
        cv::Mat colorMat;
        if( sample ){
            if( sample->color ){
                colorIm = sample->color;
                colorMat = _converter->convertPXCImageToOpenCVMat( colorIm, ImageFormatConverter::ImageFormat::STREAM_TYPE_COLOR );
            }
            cv::imshow("Color Image on OpenCV Format", colorMat);
            cv::waitKey(1);
        }
        _senseManager->ReleaseFrame();
    }
}

