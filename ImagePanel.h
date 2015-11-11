#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include "Image.h"

/**
 * TODO This class will eventually get images directly from the image manager
 */

class ImagePanel : public wxPanel{
private:
    wxBitmap mBitmapImage;
    Image* mImageForPanel;
public:
    ImagePanel(wxFrame* parent, Image* image, int bitmapType = wxBITMAP_TYPE_PNG);
    ImagePanel(wxFrame* parent, Image &image);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);

    DECLARE_EVENT_TABLE();
};