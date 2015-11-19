#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <thread>
#include "RecognitionProcess.h"
#include "ImagePanel.h"

class RecognitionApp: public wxApp
{
private:
    std::thread *m_mainProcess;
    wxSizer* sizer;
    Image* displayPicture;
    ImagePanel* imgPanel;


public:
    RecognitionProcess* process;

    virtual bool OnInit();
    virtual int OnExit();

    void SetImage(Image* img);
};