#include "wxMainFrame.h"

wxBEGIN_EVENT_TABLE(wxMainFrame, wxFrame)
    EVT_MENU(ID_SAVE,   wxMainFrame::OnSave)
    EVT_MENU(wxID_EXIT,  wxMainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, wxMainFrame::OnAbout)
    EVT_BUTTON(ID_VALID, wxMainFrame::OnValid)
    EVT_BUTTON(ID_PREV, wxMainFrame::OnPrev)
    EVT_BUTTON(ID_NEXT, wxMainFrame::OnNext)
wxEND_EVENT_TABLE()

wxMainFrame::wxMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, RecognitionApp* parent)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->parent = parent;

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SAVE, "&Save Image\tCtrl-H",
                     "Save the image");
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

    // Set the bitmap images
    wxString basePath = wxStandardPaths::Get().GetDataDir();
    basePath = basePath.substr(0, basePath.find_last_of("\\/"));
    validBitmap = new wxBitmap(basePath + wxT("\\ressources\\btnValid.bmp"), wxBITMAP_TYPE_BMP);
    nextBitmap = new wxBitmap(basePath + wxT("\\ressources\\btnNext.bmp"), wxBITMAP_TYPE_BMP);
    prevBitmap = new wxBitmap(basePath + wxT("\\ressources\\btnPrev.bmp"), wxBITMAP_TYPE_BMP);

    // Don't need to store in pointers, they are deleted when the frame is killed
    new wxBitmapButton(this, ID_PREV, *prevBitmap, wxPoint(325,0), wxSize(validBitmap->GetWidth(),validBitmap->GetHeight()) );
    new wxBitmapButton(this, ID_VALID, *validBitmap, wxPoint(325,105), wxSize(validBitmap->GetWidth(),validBitmap->GetHeight()) );
    new wxBitmapButton(this, ID_NEXT, *nextBitmap, wxPoint(325,210), wxSize(validBitmap->GetWidth(),validBitmap->GetHeight()) );

    SetStatusText( "Ready!" );
}

void wxMainFrame::OnExit(wxCommandEvent& event)
{
    if(validBitmap != NULL)
    {
        delete validBitmap;
        validBitmap = NULL;
    }
    if(nextBitmap != NULL)
    {
        delete nextBitmap;
        nextBitmap = NULL;
    }
    if(prevBitmap != NULL)
    {
        delete prevBitmap;
        prevBitmap = NULL;
    }

    Close( true );
}
void wxMainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a facial recognition module for the PFE of Samy Lemcelli and Christopher Lariviere",
                  "About Facial Recognition", wxOK | wxICON_INFORMATION );
}
void wxMainFrame::OnSave(wxCommandEvent& event)
{
    wxLogMessage("You saved an image!");
}

void wxMainFrame::OnValid(wxCommandEvent& event)
{
    this->parent->process->ValidateCurrent();
    //wxLogMessage("You clicked on Valid!");
}

void wxMainFrame::OnPrev(wxCommandEvent& event)
{
    this->parent->process->PreviousImage();
    this->parent->SetImage(this->parent->process->GetCurrentImage());
    //wxLogMessage("You clicked on Prev!");
}

void wxMainFrame::OnNext(wxCommandEvent& event)
{
    this->parent->process->NextImage();
    this->parent->SetImage(this->parent->process->GetCurrentImage());
    //wxLogMessage("You clicked on Next!");
}