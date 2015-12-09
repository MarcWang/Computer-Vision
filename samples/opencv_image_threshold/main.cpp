#include <opencv2/opencv.hpp>
#include <iostream>

const std::string keys =
        "{help      |         | print this message   }"
        ;

int main( int argc, char *argv[] )
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Image Threshold");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::Mat srcMat = cv::imread("threshold.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat binMat, binInvMat, truncMat, tozeroMat, tozeroInvMat, otsuMat, trianMat;
    cv::Mat adapMaenMat, adapGaussianMat;

    double th = 127, maxVal = 255;
    cv::threshold( srcMat, binMat, th, maxVal, cv::THRESH_BINARY );
    cv::threshold( srcMat, binInvMat, th, maxVal, cv::THRESH_BINARY_INV );
    cv::threshold( srcMat, truncMat, th, maxVal, cv::THRESH_TRUNC );
    cv::threshold( srcMat, tozeroMat, th, maxVal, cv::THRESH_TOZERO );
    cv::threshold( srcMat, tozeroInvMat, th, maxVal, cv::THRESH_TOZERO_INV );
    cv::threshold( srcMat, trianMat, th, maxVal, cv::THRESH_TRIANGLE );

    cv::threshold( srcMat, otsuMat, 0, maxVal, cv::THRESH_BINARY+cv::THRESH_OTSU );

    cv::adaptiveThreshold( srcMat, adapMaenMat, maxVal, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2 );
    cv::adaptiveThreshold( srcMat, adapGaussianMat, maxVal, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2 );

    cv::imshow("Original", srcMat);
    cv::imshow("THRESH_BINARY", binMat);
    cv::imshow("THRESH_BINARY_INV", binInvMat);
    cv::imshow("THRESH_TRUNC", truncMat);
    cv::imshow("THRESH_TOZERO", tozeroMat);
    cv::imshow("THRESH_TOZERO_INV", tozeroInvMat);
    cv::imshow("THRESH_TRIANGLE", trianMat);
    cv::imshow("THRESH_OTSU", otsuMat);
    cv::imshow("ADAPTIVE_THRESH_MEAN_C", adapMaenMat);
    cv::imshow("ADAPTIVE_THRESH_GAUSSIAN_C", adapGaussianMat);

    cv::waitKey(0);
    return 0;
}
