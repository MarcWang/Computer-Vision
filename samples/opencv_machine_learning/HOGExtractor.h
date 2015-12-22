#ifndef HOGEXTRACTOR_H
#define HOGEXTRACTOR_H
#include <opencv2/objdetect.hpp>


struct HOGParams
{
    HOGParams();
    cv::Size blockSize;
    cv::Size blockStrideSize;
    cv::Size cellSize;
    int bins;
};

class HOGExtractor
{
public:
    HOGExtractor();
    ~HOGExtractor();
    void initialize( HOGParams params, int width, int height );
    void setSVM( const char* path );
    void setSVM( std::vector< float > detector );
    void extract( cv::Mat frame, cv::Mat &resMat );
    void detect( cv::Mat frame, std::vector<cv::Rect> &result );

private:
    cv::Size _winSize;
    HOGParams _params;
    cv::HOGDescriptor *_hog;
};

#endif // HOGEXTRACTOR_H
