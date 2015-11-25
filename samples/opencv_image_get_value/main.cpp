#include <iostream>
#include <opencv2/opencv.hpp>

int64 method1(cv::Mat img)
{
    int64 start = cv::getTickCount();
    std::cout<<"Mathod1 Start"<<std::endl;
    uchar r, g, b;
    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            r = pixel[2];
            g = pixel[1];
            b = pixel[0];
        }
    }

    int64 end = cv::getTickCount();
    std::cout<<"Mathod1 End"<<std::endl;
    return end-start;
}

int64 method2( cv::Mat img )
{
    int64 start = cv::getTickCount();
    std::cout<<"Mathod2 Start"<<std::endl;

    int nChannels = img.channels();
    int nRows = img.rows;
    int nCols = img.cols * nChannels;

    if (img.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar r, g, b;
    for (i = 0; i < nRows; ++i)
    {
        for (j = 0; j < nCols; ++j)
        {
            r = img.ptr<uchar>(i)[nChannels*j + 2];
            g = img.ptr<uchar>(i)[nChannels*j + 1];
            b = img.ptr<uchar>(i)[nChannels*j + 0];
        }
    }

    int64 end = cv::getTickCount();
    std::cout<<"Mathod2 End"<<std::endl;
    return end-start;
}

//The iterator (safe) method
int64 method3( cv::Mat img )
{
    int64 startTime = cv::getTickCount();
    std::cout<<"Mathod3 Start"<<std::endl;

    cv::MatIterator_<cv::Vec3b> it, end;
    uchar r, g, b;
    for( it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; ++it)
    {
        r = (*it)[2];
        g = (*it)[1];
        b = (*it)[0];
    }

    int64 endTime = cv::getTickCount();
    std::cout<<"Mathod3 End"<<std::endl;
    return endTime-startTime;
}

int main()
{
    cv::Mat img( 1600, 2560, CV_8UC3, cv::Scalar(0,0,0));

    int64 s1 = method1(img);
    std::cout << "process time: " << s1 << std::endl;

    int64 s2 = method2(img);
    std::cout << "process time " << s2 << std::endl;

    int64 s3 = method3(img);
    std::cout << "process time " << s3 << std::endl;

    cv::imshow("show image", img);
    cv::waitKey(0);
    return 0;
}

