#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>

#define TRAIN_PERSONS 5
#define TRAIN_FACES 3
#define FEATURE_SIZE 64


void main()
{
    cv::CascadeClassifier haar_cascade;
    if( !haar_cascade.load("haarcascade_frontalface_alt.xml") ){
        std::cout<<"Initialize Error: load face cascade"<<std::endl;
    }

    int deviceId = 0;
    std::cout<<"Choose Webcam(0~3)"<<std::endl;
    std::cin>>deviceId;
    cv::VideoCapture cap(deviceId);
    if(!cap.isOpened()) {
        std::cout<<"Open capture device ID "<<deviceId<<" error"<<std::endl;
    }

    bool trainFlag = true;
    std::cout<<"Train Mode"<<std::endl;
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    cv::Mat camMat;
    for( int i = 0; i < TRAIN_PERSONS; i++) {
        for( int j = 0; j < TRAIN_FACES; j++) {
            while(trainFlag) {
                cap >> camMat;

                cv::imshow("Display Frame", camMat);
                char key = (char) cv::waitKey(20);
                if( key == 'T' || key == 't' ){

                    cv::Mat gray;
                    cv::cvtColor( camMat, gray, CV_BGR2GRAY );
                    std::vector< cv::Rect_<int> > faces;
                    cv::equalizeHist( gray, gray );
                    haar_cascade.detectMultiScale( gray,
                                              faces,
                                              1.1,
                                              4,
                                              cv::CASCADE_SCALE_IMAGE,
                                              cv::Size(128, 128) );
                    if( faces.size() > 0 ){
                        cv::Rect faceRect = faces[0];
                        cv::Mat faceMat = gray(faceRect);
                        cv::Mat resizeMat;
                        cv::resize(faceMat, resizeMat, cv::Size(FEATURE_SIZE, FEATURE_SIZE), 1.0, 1.0, cv::INTER_CUBIC);
                        images.push_back(resizeMat);
                        labels.push_back(i);
                        std::cout<<"Register person :"<< i <<std::endl;
                        cv::imshow("Register Person Image", faceMat);
                    }
                    break;
                }
            }
        }
        std::cout<<"Next Person"<<std::endl;
    }

    std::cout<<"Create a FaceRecognizer"<<std::endl;
    cv::Ptr<cv::face::FaceRecognizer> model = cv::face::createEigenFaceRecognizer();

//    model->load("eigenface.yml");
    model->train(images, labels);
    model->save("eigenface.yml");

    while( true ) {
        cap >> camMat;
        cv::Mat grayMat;
        cv::cvtColor(camMat, grayMat, CV_BGR2GRAY);
        std::vector< cv::Rect_<int> > faces;
        cv::equalizeHist( grayMat, grayMat );
        haar_cascade.detectMultiScale( grayMat,
                                  faces,
                                  1.1,
                                  3,
                                  cv::CASCADE_SCALE_IMAGE,
                                  cv::Size(64, 64) );

        for( int i = 0; i < (int)faces.size(); i++) {
            cv::Rect face_i = faces[i];
            cv::Mat faceMat = grayMat(face_i);
            cv::Mat resizeMat;
            cv::resize(faceMat, resizeMat, cv::Size(FEATURE_SIZE, FEATURE_SIZE), 1.0, 1.0, cv::INTER_CUBIC);


            int predictedLabel = -1;
            double confidence = 0.0;
            model->predict( resizeMat, predictedLabel, confidence );

//            int prediction = model->predict(resizeMat);

            cv::rectangle(camMat, face_i, CV_RGB(0, 255,0), 1);
            std::string box_text = cv::format("Prediction = %d, Confidence = %d", predictedLabel, (int)confidence);
            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);
            cv::putText(camMat, box_text, cv::Point(pos_x, pos_y), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
        }
        cv::imshow("Face Recognizer", camMat);
        char key = (char) cv::waitKey(20);
        if(key == 27)
            break;
    }
}
