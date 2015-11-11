#include "RecognitionProcess.h"


RecognitionProcess::RecognitionProcess(ImageManager *pManager)
{
    int label = -1;
    double confidence = 0.0;
    this->imageManager = pManager;
    this->model = createEigenFaceRecognizer();
    this->model->train(pManager->getOpenCVTrainImages(), pManager->getTrainLabels());
    for(Mat imageToTest : pManager->getOpenCVTestImages())
    {
        this->model->predict(imageToTest, label, confidence);
        cout << "Class: " << label
            << " The ressemblance to the test image is: " << confidence << endl;
    }
}


