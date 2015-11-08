//
// Created by Chris on 11/7/2015.
//

#include "ImagePanel.h"



BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
    EVT_PAINT(ImagePanel::paintEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent, Image* image)
{
    this->m_parent = parent;
    this->mImageForPanel = image;
}
ImagePanel::ImagePanel(wxFrame* parent, Image &image)
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
    dc.DrawBitmap(bitmapImage, 0, 0, false );
}