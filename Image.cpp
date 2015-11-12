#include "Image.h"

Image::Image(std::string &path, int imagetype)
{
    this->mImagePath = path;
    this->mLoadedType = imagetype;
    this->mImageMatrix = imread(path, imagetype);

    if(mImageMatrix.data != nullptr)
    {
        this->convertToRGB();
    }
}

Image::Image(wxImage& img){}

void Image::convertToRGB()
{
    if(mLoadedType == CV_LOAD_IMAGE_COLOR)
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