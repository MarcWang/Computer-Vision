#ifndef IMAGEFORMATCONVERTER_H
#define IMAGEFORMATCONVERTER_H
#include <opencv2\opencv.hpp>
#include <pxcimage.h>

#define LIB_DECL __declspec(dllexport)

class LIB_DECL ImageFormatConverter
{
public:
    enum ImageFormat {
        STREAM_TYPE_COLOR = 0,
        STREAM_TYPE_DEPTH = 1,
        STREAM_TYPE_IR = 2
    };
public:
    ImageFormatConverter();
    cv::Mat convertPXCImageToOpenCVMat( PXCImage *pxcImg, ImageFormat format);
};

#endif // IMAGEFORMATCONVERTER_H
