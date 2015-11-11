
#include "wxMainFrame.h"
#include <thread>
#include "RecognitionProcess.h"
#include "ImagePanel.h"

class RecognitionApp: public wxApp
{
private:
    //std::thread *m_mainProcess;
public:
    virtual bool OnInit();
    virtual int OnExit();
};


wxIMPLEMENT_APP(RecognitionApp);
bool RecognitionApp::OnInit()
{
    ImageManager* manager = new ImageManager("../../Images/train", "../../Images/test");
    RecognitionProcess* process = new RecognitionProcess(manager);

    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxMainFrame *frame = new wxMainFrame( wxT("FacialRecognitionModule"), wxPoint(50, 50), wxSize(450, 340) );

    string path = "../../Images/train/samy01_0.jpg";

    Image* samyPic = new Image(path);
    ImagePanel* imgPanel = new ImagePanel(frame, samyPic);

    sizer->Add(imgPanel, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->Show( true );

    //m_mainProcess = new std::thread(&RecognitionProcess::RecognitionProcess, this);

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

    return 0;
}