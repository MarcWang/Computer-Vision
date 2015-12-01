#include "SVMProcess.h"

SVMProcess::SVMProcess()
{  
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    // edit: the params struct got removed,
    // we use setter/getter now:
//    svm->setType(ml::SVM::C_SVC);
//    svm->setKernel(ml::SVM::POLY);
//    svm->setGamma(3);

//    Mat trainData; // one row per feature
//    Mat labels;
//    svm->train( trainData , ml::ROW_SAMPLE , labels );
//    // ...
//    Mat query; // input, 1channel, 1 row (apply reshape(1,1) if nessecary)
//    Mat res;   // output
//    svm->predict(query, res);
}

