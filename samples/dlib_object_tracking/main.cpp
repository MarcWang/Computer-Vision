#include <iostream>

#include <opencv/include/opencv2/opencv.hpp>
#include <dlib/include/image_processing.h>
#include <dlib/include/image_io.h>
#include <dlib/include/opencv.h>
#include <dlib/include/image_transforms.h>

#include "MouseManipulator.h"

int main()
{
    cv::VideoCapture cap(0);
    dlib::correlation_tracker tracker;

    cv::namedWindow( "Demo", 1 );
    MouseManipulator mouseHandler;
    mouseHandler.initialize( "Demo" );

    bool trackFlag = false;
    while( true )
    {
        cv::Mat cvImage;
        cv::Mat cpyMat;
        cap >> cvImage;
        if( cvImage.empty() ){
            break;
        }
        cvImage.copyTo( cpyMat );

        dlib::array2d<dlib::rgb_pixel> dColorImg;
        dlib::array2d<unsigned char> dGrayImg;
        char key = (char)cv::waitKey(20);
        if(key == 27){
            break;
        }

        if( trackFlag ){
            dlib::assign_image( dColorImg, dlib::cv_image<dlib::bgr_pixel>(cvImage));
            dlib::assign_image( dGrayImg, dColorImg);

            tracker.update(dGrayImg);
            dlib::drectangle rect = tracker.get_position();

            int left = cvRound( rect.left() );
            int top = cvRound( rect.top() );
            int right = cvRound( rect.left() + rect.width()-1 );
            int bottom = cvRound( rect.top() + rect.height()-1 );
            cv::rectangle( cpyMat,
                           cvPoint( left, top ),
                           cvPoint( right, bottom ),
                           CV_RGB(0,0,255), 3, 8, 0);
        }


        if( mouseHandler.hasSelection() ){
            cv::Rect rect = mouseHandler.getSelectRect();

            dlib::array2d<dlib::rgb_pixel> dColorImg;
            dlib::assign_image( dColorImg, dlib::cv_image<dlib::bgr_pixel>(cvImage));
            dlib::assign_image(dGrayImg, dColorImg);

            tracker.start_track(dGrayImg, dlib::centered_rect( dlib::point( rect.x + rect.width/2 , rect.y + rect.height/2), rect.width, rect.height));
            trackFlag = true;
            mouseHandler.clear();

        }
        else{
            cv::Rect rect = mouseHandler.getSelectRect();
            cv::Mat roi( cpyMat, rect );
            cv::bitwise_not( roi, roi );
        }

        cv::imshow("Demo", cpyMat);
    }
}

