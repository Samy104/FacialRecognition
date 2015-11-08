#include "wxMainFrame.h"

wxBEGIN_EVENT_TABLE(wxMainFrame, wxFrame)
    EVT_MENU(ID_Hello,   wxMainFrame::OnHello)
    EVT_MENU(wxID_EXIT,  wxMainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, wxMainFrame::OnAbout)
wxEND_EVENT_TABLE()

wxMainFrame::wxMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Save Image\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Loading the images!" );
}

void wxMainFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void wxMainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a facial recognition module for the PFE of Samy Lemcelli and Christopher Lariviere",
                  "About Facial Recognition", wxOK | wxICON_INFORMATION );
}
void wxMainFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("You saved an image!");
}