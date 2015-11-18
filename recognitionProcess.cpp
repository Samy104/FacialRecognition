#include "RecognitionProcess.h"


RecognitionProcess::RecognitionProcess(ImageManager *pManager)
{
    endpoint = new WebSocketConnector();
    endpoint->run("ws://garbinc.ddns.net:9000");
    int label = -1;
    double confidence = 0.0;
    this->imageManager = pManager;
    this->model = createEigenFaceRecognizer(10, 100.0);
    this->model->train(*pManager->getOpenCVTrainImages(), pManager->getTrainLabels());

    vector<Mat>* pTestImageVector = pManager->getOpenCVTestImages();
    for(int imageIndex = 0; imageIndex < pTestImageVector->size(); ++imageIndex)
    {
        this->model->predict(pTestImageVector->at(imageIndex), label, confidence);


        // One we have a match call the door command
        int imageLabel = pManager->getTestLabels()[imageIndex];
        if(label == imageLabel)
        {
            cout << "Accepted => Class: " << label
            << " The ressemblance to the test image is: " << confidence << endl;

            ContactServer();
        }
        else
        {
            cout << "Rejected => Class: " << label
            << " The ressemblance to the test image is: " << confidence << endl;
        }

    }
}

RecognitionProcess::~RecognitionProcess()
{
    if(endpoint != NULL)
    {
        delete endpoint;
        endpoint = NULL;
    }
}

void RecognitionProcess::ContactServer()
{
    endpoint->m_client.send(endpoint->m_hd1, "", websockettpp::frame::opcode::text,endpoint->ec);
}


