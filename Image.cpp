#include "Image.h"

Image::Image(std::string &path)
{
    this->mImagePath = path;
    this->mImageMatrix = imread(path, CV_LOAD_IMAGE_COLOR);
    if(mImageMatrix.data != nullptr)
    {
        this->convertToRGB();
    }
}

Image::Image(wxImage& img){}

void Image::printImageMatrix()
{
    cout << this->mImageMatrix.rows;
}

void Image::convertToRGB()
{
    cvtColor(this->mImageMatrix, this->mImageMatrix, CV_BGR2RGB);
    this->mImage = new wxImage(this->mImageMatrix.cols, this->mImageMatrix.rows, this->mImageMatrix.data, true);
}

Mat Image::getOpenCVMatrix()
{
    return this->mImageMatrix;
}

wxImage* Image::getWxImage()
{
    return this->mImage;
}