#include <iostream>
#include <IFaceCoreModule.h>
#include <FaceOpenCVModule.h>
#include <FaceDlibModule.h>


void drawFaceInfo( cv::Mat &img, MFaceResult opencvResult, MFaceResult dlibResult ){

    std::vector<MFaceInfo> opencvFaces = opencvResult.infos;
    for( std::vector<MFaceInfo>::const_iterator r = opencvFaces.begin(); r != opencvFaces.end(); r++ )
    {
        MFaceInfo info = *r;
        int left = cvRound( info.rect.x );
        int top = cvRound( info.rect.y );
        int right = cvRound( info.rect.x + info.rect.width-1 );
        int bottom = cvRound( info.rect.y + info.rect.height-1 );
        cv::rectangle( img,
                       cvPoint( left, top ),
                       cvPoint( right, bottom ),
                       CV_RGB(0,0,255), 3, 8, 0);
    }

    std::vector<MFaceInfo> dlibFaces = dlibResult.infos;
    for( std::vector<MFaceInfo>::const_iterator r = dlibFaces.begin(); r != dlibFaces.end(); r++ )
    {
        MFaceInfo info = *r;
        int left = cvRound( info.rect.x );
        int top = cvRound( info.rect.y );
        int right = cvRound( info.rect.x + info.rect.width-1 );
        int bottom = cvRound( info.rect.y + info.rect.height-1 );
        cv::rectangle( img,
                       cvPoint( left, top ),
                       cvPoint( right, bottom ),
                       CV_RGB(255,0,0), 3, 8, 0);
    }
}

void main()
{
    cv::VideoCapture cap(1);

    IFaceCoreModule *faceHandler = new FaceOpenCVModule();
    faceHandler->initialize();

    IFaceCoreModule *faceDlibHandler = new FaceDlibModule();
    faceDlibHandler->initialize();

    while( true )
    {
        cv::Mat cvImage;
        cap >> cvImage;
        if( cvImage.empty() ){
            break;
        }

        double t = 0;
        t = (double)cvGetTickCount();
        MFaceResult opencvResult;
        faceHandler->detection( cvImage, opencvResult);
        t = (double)cvGetTickCount() - t;
        std::cout<<"OpenCV Detect Time = "<< t/1000 <<std::endl;


        double t1 = 0;
        t1 = (double)cvGetTickCount();
        MFaceResult dlibResult;
        faceDlibHandler->detection( cvImage, dlibResult);
        t1 = (double)cvGetTickCount() - t1;
        std::cout<<"Dlib Detect Time = "<< t1/1000 <<std::endl;

        std::cout<<"---------------------------------------------"<<std::endl;

        drawFaceInfo( cvImage, opencvResult, dlibResult);
        cv::waitKey(1);
        cv::imshow( "result", cvImage );
    }
}

