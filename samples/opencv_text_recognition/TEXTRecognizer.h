#ifndef TEXTRECOGNIZER_H
#define TEXTRECOGNIZER_H
#include "opencv2/text.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define LIB_DECL __declspec(dllexport)

class LIB_DECL TEXTRecognizer
{
public:
    TEXTRecognizer();
    ~TEXTRecognizer();
    void initialize( );
    void initialize( std::vector<std::string> lexicon );

    void textDecode( cv::Mat roiMat, std::string &text, float &confidence );
    void charDecode( cv::Mat roiMat, std::string &character, double &confidence );

private:
    cv::Ptr<cv::text::OCRHMMDecoder::ClassifierCallback> _ocrProc;
    cv::Ptr<cv::text::OCRBeamSearchDecoder> _txtProc;
    std::string _vocabulary;
    cv::Mat _transition_p;
};

#endif // TEXTRECOGNIZER_H
