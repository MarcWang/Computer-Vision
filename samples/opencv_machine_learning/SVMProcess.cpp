#include "SVMProcess.h"

SVMProcess::SVMProcess()
{  
    _svm = cv::ml::SVM::create();

////    C_SVC =100,
////    NU_SVC =101,
////    ONE_CLASS =102,
////    EPS_SVR =103,
////    NU_SVR =104
//    _svm->setType(cv::ml::SVM::C_SVC);

////    LINEAR =0,
////    POLY =1,
////    RBF =2,
////    SIGMOID =3,
////    CHI2 =4,
////    INTER =5
//    cv::ml::SVM::KernelTypes kernelType = cv::ml::SVM::RBF;
//    _svm->setKernel(kernelType);

    _svm->setCoef0(0.0);
    _svm->setDegree(3);
    _svm->setTermCriteria(cv::TermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 1e-3 ));
    _svm->setGamma(0);
    _svm->setKernel(cv::ml::SVM::LINEAR);
    _svm->setNu(0.5);
    _svm->setP(0.1); // for EPSILON_SVR, epsilon in loss function?
    _svm->setC(0.01); // From paper, soft classifier
    _svm->setType(cv::ml::SVM::EPS_SVR); // C_SVC; // EPSILON_SVR; // may be also NU_SVR; // do regression task



//    if( kernelType == cv::ml::SVM::RBF ){
//        _svm->setGamma(3);
//    }

//    cv::TermCriteria criteria( CV_TERMCRIT_EPS, 1000 , FLT_EPSILON );
//    _svm->setTermCriteria( criteria );

    dataFlag = false;

}

bool SVMProcess::pushTrainData( cv::Mat srcData, int label )
{
    if( !dataFlag ){
        dataFlag = !dataFlag;
        _trainData.push_back(srcData);
        _trainLabel.push_back(label);
        return true;
    }else{
        if( _trainData.cols != srcData.cols ){
            std::cout<<"push data is not correction"<<std::endl;
            return false;
        }else{
            _trainData.push_back(srcData);
            _trainLabel.push_back(label);
            return true;
        }
    }
}

int SVMProcess::getTrainDataCounts()
{
    int counts = _trainData.rows;
    return counts;
}

void SVMProcess::clearTrainData()
{
    _trainData.release();
    _trainLabel.release();
}

std::vector<float> SVMProcess::outputDetector()
{
    return _hogFeature;
}

void SVMProcess::train()
{
    _svm->train( _trainData , cv::ml::ROW_SAMPLE , _trainLabel );
    _svm->save("train.xml");
//    cv::FileStorage file;

//    file.open("123.txt", cv::FileStorage::WRITE );
//    _svm->write(file);

    // get the support vectors
    cv::Mat sv = _svm->getSupportVectors();
    const int sv_total = sv.rows;
    // get the decision function
    cv::Mat alpha, svidx;
    double rho = _svm->getDecisionFunction(0, alpha, svidx);
    CV_Assert( alpha.total() == 1 && svidx.total() == 1 && sv_total == 1 );
    CV_Assert( (alpha.type() == CV_64F && alpha.at<double>(0) == 1.) ||
               (alpha.type() == CV_32F && alpha.at<float>(0) == 1.f) );
    CV_Assert( sv.type() == CV_32F );


    std::vector< float > hog_detector;
    hog_detector.clear();
    hog_detector.resize(sv.cols + 1);

    memcpy( &hog_detector[0], sv.ptr(), sv.cols*sizeof(hog_detector[0]) );
    hog_detector[sv.cols] = (float)-rho;

    _hogFeature = hog_detector;

    FILE* fp = fopen("hog.txt","wb");
    if( NULL == fp ){
        return;
    }

    for( std::vector<float>::const_iterator r = hog_detector.begin(); r != hog_detector.end(); r++ ){
        fprintf( fp,"%f \n", *r );
    }

    fclose(fp);
}

void SVMProcess::predict( cv::Mat srcData, int &label )
{
    cv::Mat res;
    _svm->predict( srcData, res);
    label = res.ptr<int>(0)[0];
}

