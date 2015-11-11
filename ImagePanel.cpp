//
// Created by Chris on 11/7/2015.
//

#include "ImagePanel.h"



BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
    EVT_PAINT(ImagePanel::paintEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent, Image* image, int bitmapType)
    :wxPanel(parent, -1, wxPoint(-1, -1), wxSize(250, 250))
{
    this->m_parent = parent;
    this->mImageForPanel = image;
}
ImagePanel::ImagePanel(wxFrame* parent, Image &image)
        :wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1))
{

}

void ImagePanel::paintEvent(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    render(dc);
}
void ImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}
void ImagePanel::render(wxDC& dc)
{
    wxBitmap bm(mImageForPanel->getWxImage()->Copy());
    dc.DrawBitmap(bm,0,0,false);
}