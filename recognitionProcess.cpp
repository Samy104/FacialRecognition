#include "RecognitionProcess.h"


RecognitionProcess::RecognitionProcess(string websocketIP, string trainingImages, string testingImages)
{
    m_Manager = new ImageManager(trainingImages, testingImages);
    endpoint = new WebSocketConnector();
    endpoint->run(websocketIP.c_str());
    int label = -1;
    double confidence = 0.0;
    this->imageManager = m_Manager;
    this->model = createEigenFaceRecognizer(10, 100.0);
    this->model->train(*m_Manager->getOpenCVTrainImages(), m_Manager->getTrainLabels());

    vector<Mat>* pTestImageVector = m_Manager->getOpenCVTestImages();
    for(int imageIndex = 0; imageIndex < pTestImageVector->size(); ++imageIndex)
    {
        this->model->predict(pTestImageVector->at(imageIndex), label, confidence);

        // One we have a match call the door command
        int imageLabel = m_Manager->getTestLabels()[imageIndex];
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

    if(m_Manager != NULL)
    {
        delete m_Manager;
        m_Manager = NULL;
    }
}

void RecognitionProcess::ContactServer()
{
    endpoint->m_client.send(endpoint->getNetworkHandle(), "100,tabletoplight,1", websocketpp::frame::opcode::text, endpoint->getErrorCode());
}


