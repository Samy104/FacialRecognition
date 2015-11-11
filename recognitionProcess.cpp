#include "RecognitionProcess.h"


RecognitionProcess::RecognitionProcess()
{
    model = createEigenFaceRecognizer(0, 110.0);
}

RecognitionProcess::RecognitionProcess(ImageManager *pManager)
{
    this->imageManager = pManager;
    this->model = createEigenFaceRecognizer();
    this->model->train(pManager->getOpenCVTrainImages(), pManager->getTrainLabels());
    /*
     * this is the error.
     * try{
        int prediction = this->model->predict(pManager->getOpenCVTestImages()[0]);
    }catch(exception e){
        cout << e.what();
    }*/
}

Mat RecognitionProcess::normalizeImageMatrix(Mat incoming)
{
    Mat out;
    cv::normalize(incoming, out, 0, 255, NORM_MINMAX, CV_8UC1);
    cv::normalize(incoming, out, 0, 255, NORM_MINMAX, CV_8UC3);
}


