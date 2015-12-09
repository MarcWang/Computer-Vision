#include <opencv2/opencv.hpp>
#include <iostream>

const std::string keys =
        "{help      |         | print this message   }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Integral Image");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::Mat srcMat = cv::imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat sumMat, sqSumMat;
    cv::integral( srcMat, sumMat, sqSumMat );

    cv::imshow("srcMat", srcMat);

    cv::waitKey(0);
    return 0;
}
