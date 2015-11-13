#include <iostream>
#include <IFaceCoreModule.h>
#include <FaceOpenCVModule.h>
#include <FaceDlibModule.h>

void drawFaceInfo( cv::Mat &img, MFaceResult result, int color ){

    cv::Scalar drawColor;
    if( color == 0 ){
        drawColor = CV_RGB(0,0,255);
    }else{
        drawColor = CV_RGB(255,0,0);
    }
    std::vector<MFaceInfo> opencvFaces = result.infos;
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
                       drawColor, 3, 8, 0);
    }
}


void main()
{
    cv::VideoCapture cap(1);

    IFaceCoreModule *faceOpenCVHandler = new FaceOpenCVModule();
    faceOpenCVHandler->initialize();

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
        faceOpenCVHandler->detection( cvImage, opencvResult);
        t = (double)cvGetTickCount() - t;
        std::cout<<"OpenCV Detect Time = "<< t/1000 <<std::endl;
        drawFaceInfo( cvImage, opencvResult, 1);

        double t1 = 0;
        t1 = (double)cvGetTickCount();
        MFaceResult dlibResult;
        faceDlibHandler->detection( cvImage, dlibResult);
        t1 = (double)cvGetTickCount() - t1;
        std::cout<<"Dlib Detect Time = "<< t1/1000 <<std::endl;
        drawFaceInfo( cvImage, dlibResult, 0);
        std::cout<<"---------------------------------------------"<<std::endl;

        cv::waitKey(1);
        cv::imshow( "result", cvImage );
    }

    if( faceOpenCVHandler != NULL ){
        delete faceOpenCVHandler;
    }
    if( faceDlibHandler != NULL ){
        delete faceDlibHandler;
    }
}

