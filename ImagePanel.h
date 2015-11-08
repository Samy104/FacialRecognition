//
// Created by Chris on 11/7/2015.
//

#ifndef FACIALRECOGNITION_IMAGEPANEL_H
#define FACIALRECOGNITION_IMAGEPANEL_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include "Image.h"

/**
 * TODO This class will eventually get images directly from the image manager
 */

class ImagePanel : public wxPanel{
private:
    wxBitmap bitmapImage;
    Image* mImageForPanel;
public:
    ImagePanel(wxFrame* parent, Image* image);
    ImagePanel(wxFrame* parent, Image &image);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);

    DECLARE_EVENT_TABLE();
};

#endif //FACIALRECOGNITION_IMAGEPANEL_H
