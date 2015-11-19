#include "RecognitionProcess.h"

RecognitionProcess* G_ProcessPointer;

RecognitionProcess::RecognitionProcess(string websocketIP, string trainingImages, string testingImages, bool emulateCamera)
{
    // Keep a reference to the base class for the sharable variables
    G_ProcessPointer = this;

    // Create the Image Manager for the Main Recognition Process
    imageManager = new ImageManager(trainingImages, testingImages);

    // Establish the connection to the WebSocket Server
    endpoint = new WebSocketConnector();
    endpoint->run(websocketIP.c_str());

    // Train the model using the training images.
    G_ProcessPointer->model = createEigenFaceRecognizer(10, 100.0);
    G_ProcessPointer->model->train(*imageManager->getOpenCVTrainImages(), imageManager->getTrainLabels());

    // Set the member variables
    G_ProcessPointer->m_emulateCamera = emulateCamera;
    G_ProcessPointer->m_validateNext = false;
}

RecognitionProcess::~RecognitionProcess()
{
    if(endpoint != NULL)
    {
        delete endpoint;
        endpoint = NULL;
    }

    if(imageManager != NULL)
    {
        delete imageManager;
        imageManager = NULL;
    }
}

void RecognitionProcess::ContactServer()
{
    endpoint->m_client.send(endpoint->getNetworkHandle(), "100,tabletoplight,1", websocketpp::frame::opcode::text, endpoint->getErrorCode());
}

void RecognitionProcess::Run()
{
    G_ProcessPointer->m_isAlive = true;

    while(G_ProcessPointer->m_isAlive)
    {
        if(G_ProcessPointer->m_emulateCamera)
        {
            if(G_ProcessPointer->m_validateNext)
            {
                // Inspect the image
                vector<Mat>* pTestImageVector = imageManager->getOpenCVTestImages();

                G_ProcessPointer->model->predict(pTestImageVector->at(currentImageID), label, confidence);

                // One we have a match call the door command
                int imageLabel = imageManager->getTestLabels()[currentImageID];
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

                G_ProcessPointer->m_validateNext = false;
            }
        }
        else
        {
            // Inspect the image
            Mat pCameraVector; // Samy: To set with the camera frame image when the connecter is done.
            G_ProcessPointer->model->predict(pCameraVector, label, confidence);

            // One we have a match call the door command
            if(label != -1)
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

}

void RecognitionProcess::Kill()
{
    G_ProcessPointer->m_isAlive = false;
}

void RecognitionProcess::ValidateCurrent()
{
    // If emulated, grab from the image vectors.
    if(G_ProcessPointer->m_emulateCamera)
    {
        G_ProcessPointer->m_validateNext = true;

    }
    else // Use camera frame
    {

    }
}

void RecognitionProcess::NextImage()
{
    ++currentImageID;
    // If emulated, check if you are at the end of the images
    if(G_ProcessPointer->m_emulateCamera)
    {
        if(currentImageID > imageManager->getOpenCVTestImages()->size()-1)
        {
            currentImageID = 0;
        }
    }
    else // Grab the next frame from the camera
    {
        G_ProcessPointer->m_validateNext = true;
    }

    cout  << "Current Image Index: " << currentImageID << endl;
}

void RecognitionProcess::PreviousImage()
{
    // Only allow when camera is emulated
    if(G_ProcessPointer->m_emulateCamera)
    {
        --currentImageID;
        if(currentImageID < 0)
        {
            G_ProcessPointer->currentImageID = imageManager->getOpenCVTestImages()->size()-1;
        }
    }

   cout  << "Current Image Index: " << currentImageID << endl;
}

Image* RecognitionProcess::GetCurrentImage()
{
    if(G_ProcessPointer->m_emulateCamera)
    {
        return &G_ProcessPointer->imageManager->getTestImages()->at(currentImageID);
    }
    else
    {
        return NULL;
    }

}
