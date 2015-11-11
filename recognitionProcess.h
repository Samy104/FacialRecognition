#pragma once
#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include "ImageManager.h"

using namespace cv;
using namespace cv::face;
using namespace std;

class RecognitionProcess {
private:
    ImageManager* imageManager;
public:
    RecognitionProcess(ImageManager *pManager);

    Ptr<FaceRecognizer> model;
};