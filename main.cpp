
#include "wxMainFrame.h"
#include <thread>
#include "RecognitionProcess.h"
#include "ImagePanel.h"

class RecognitionApp: public wxApp
{
private:
    //std::thread *m_mainProcess;
    wxSizer* sizer;
    wxMainFrame *frame;
    Image* displayPicture;
    ImagePanel* imgPanel;

    RecognitionProcess* process;
public:
    virtual bool OnInit();
    virtual int OnExit();
};


wxIMPLEMENT_APP(RecognitionApp);
bool RecognitionApp::OnInit()
{
    // Parse the arguments
    std::string websocketIP = "ws://";
    std::string trainingImages = "";
    std::string testingImages = "";
    if(argc == 4) // All necessary arguments are given
    {
        websocketIP.append(argv[1]);
        trainingImages.append(argv[2]);
        testingImages.append(argv[3]);
    }
    else if(argc == 2) // Only the IP is given
    {

        websocketIP.append(argv[1]);
        trainingImages = "../../Images/train";
        testingImages = "../../Images/test";
    }
    else // Default values
    {
        websocketIP = "ws://garbinc.ddns.net:9000";
        trainingImages = "../../Images/train";
        testingImages = "../../Images/test";
    }

    process = new RecognitionProcess(websocketIP, trainingImages, testingImages);

    sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxMainFrame( wxT("FacialRecognitionModule"), wxPoint(50, 50), wxSize(450, 340) );

    // Samy: To change. Image should be changed by the process using the pointers.
    string path = "../../Images/train/samy01_0.jpg";

    displayPicture = new Image(path);
    imgPanel = new ImagePanel(frame, displayPicture);

    sizer->Add(imgPanel, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->Show( true );

    //m_mainProcess = new std::thread(&RecognitionProcess::RecognitionProcess, this, websocketIP, trainingImages, testingImages);

    return true;
}

int RecognitionApp::OnExit()
{
   /* m_mainProcess->join();

    if(m_mainProcess != NULL)
    {
        delete m_mainProcess;
        m_mainProcess = NULL;
    }*/

    if(sizer != NULL)
    {
        delete sizer;
        sizer = NULL;
    }
    if(frame != NULL)
    {
        delete frame;
        frame = NULL;
    }
    if(displayPicture != NULL)
    {
        delete displayPicture;
        displayPicture = NULL;
    }
    if(imgPanel != NULL)
    {
        delete imgPanel;
        imgPanel = NULL;
    }
    if(process != NULL)
    {
        delete process;
        process = NULL;
    }

    return 0;
}