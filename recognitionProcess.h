#pragma once
#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include "ImageManager.h"
#include "WebSocketConnector.h"

using namespace cv;
using namespace cv::face;
using namespace std;

class RecognitionProcess {
private:
    ImageManager* imageManager;
    WebSocketConnector *endpoint;

    void ContactServer();
public:
    RecognitionProcess(ImageManager *pManager);
    ~RecognitionProcess();

    Ptr<FaceRecognizer> model;
};