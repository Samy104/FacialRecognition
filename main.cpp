
#include "wxMainFrame.h"
#include <thread>
#include "RecognitionProcess.h"
#include "Image.h"
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
    //wxInitAllImageHandlers();

    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxMainFrame *frame = new wxMainFrame( "Facial Recognition Module", wxPoint(50, 50), wxSize(450, 340) );

    Image* samyPic = new Image("Images/samy01.jpg");
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