#pragma once

#include "main.h"
#include <wx/stdpaths.h>

class wxMainFrame : public wxFrame{
public:
    enum
    {
        ID_SAVE = 1,
        ID_VALID,
        ID_PREV,
        ID_NEXT
    };

    wxMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, RecognitionApp* parent);
private:
    RecognitionApp* parent;

    wxBitmap* validBitmap;
    wxBitmap* nextBitmap;
    wxBitmap* prevBitmap;

    void OnSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnValid(wxCommandEvent& event);
    void OnPrev(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();

};