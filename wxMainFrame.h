#ifndef __FACERECMAINFRAME_H__
#define __FACERECMAINFRAME_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class wxMainFrame : public wxFrame{
public:
    enum
    {
        ID_Hello = 1
    };

    wxMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();

};

#endif
