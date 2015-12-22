#ifndef SVMPROCESS_H
#define SVMPROCESS_H
#include <opencv2/ml.hpp>

struct SVMParams
{
    SVMParams();
    cv::ml::SVM::Types type;
    cv::ml::SVM::KernelTypes kernelType;
    cv::TermCriteria criteria;
};

class SVMProcess
{
public:
    SVMProcess();

    bool pushTrainData( cv::Mat srcData, int label );
    int getTrainDataCounts();
    void clearTrainData();

    std::vector< float > outputDetector();
    void train();
    void predict( cv::Mat srcData, int &label );

private:
    cv::Ptr<cv::ml::SVM> _svm;
    cv::Mat _trainData;
    cv::Mat _trainLabel;
    std::vector< float > _hogFeature;
    bool dataFlag;
};

#endif // SVMPROCESS_H
