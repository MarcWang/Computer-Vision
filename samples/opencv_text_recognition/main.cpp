#include <iostream>
#include <TEXTRecognizer.h>

void main()
{
    TEXTRecognizer textHandler;
//    std::vector<std::string> lexicon;
//    lexicon.push_back(std::string("CHINA"));
//    textHandler.initialize( lexicon );
    textHandler.initialize();


    cv::Mat charMat = cv::imread("scenetext_char01.jpg");
    std::string str;
    double confidence;
    textHandler.charDecode( charMat, str, confidence);
    std::cout << "Character = " << str << ", Confidence = " << confidence << std::endl;


    cv::Mat txtMat = cv::imread("scenetext_word01.jpg");
    std::string output;
    float confidences;
    textHandler.textDecode( txtMat, output, confidences);
    std::cout << "Text = "<< output <<", Confidence = "<<confidences<< std::endl;

}
