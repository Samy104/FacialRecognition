#include "main.h"
#include "wxMainFrame.h"

wxMainFrame *m_frame;


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
    m_frame = new wxMainFrame( wxT("FacialRecognitionModule"), wxPoint(50, 50), wxSize(450, 450), this );

    displayPicture = process->GetCurrentImage();
    imgPanel = new ImagePanel(m_frame, displayPicture);

    sizer->Add(imgPanel, 1, wxEXPAND);

    m_frame->SetSizer(sizer);
    m_frame->Show( true );

    m_mainProcess = new std::thread(std::bind(&RecognitionProcess::Run, process));
    return true;
}

int RecognitionApp::OnExit()
{

    if(m_mainProcess != NULL)
    {
        delete m_mainProcess;
        m_mainProcess = NULL;
    }

    if(sizer != NULL)
    {
        delete sizer;
        sizer = NULL;
    }
    if(m_frame != NULL)
    {
        delete m_frame;
        m_frame = NULL;
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

void RecognitionApp::SetImage(Image* img)
{
    displayPicture = img;
    imgPanel->paintNow();
}