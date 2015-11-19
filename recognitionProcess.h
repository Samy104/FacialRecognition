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

    bool m_emulateCamera;
    bool m_isAlive;
    bool m_validateNext;

    int currentImageID;

    // Current image vector

    // Results
    int label = -1;
    double confidence = 0.0;
public:
    RecognitionProcess(string websocketIP, string trainingImages, string testingImages, bool emulateCamera = true);
    ~RecognitionProcess();

    Ptr<BasicFaceRecognizer> model;

    void Run();
    void Kill();

    // Methods that communicate with the process thread
    void ValidateCurrent();
    void NextImage();
    void PreviousImage();

    // Returns the pointer of the current image
    Image* GetCurrentImage();
};