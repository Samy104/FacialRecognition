#pragma once

#include <string>
#include <vector>
#include <wx/wx.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class Image{
private:
    string mImagePath;
    Mat mImageMatrix;
    wxImage* mImage;

    void convertToRGB();
public:
    Image(std::string &path);
    Image(wxImage& img);

    Mat getOpenCVMatrix();
    wxImage* getWxImage();

    void printImageMatrix();
};