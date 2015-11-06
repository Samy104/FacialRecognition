#include "Image.h"

Image::Image(std::string &path)
{
    this->mImagePath = path;
    //this->mImageMatrix = new Mat(480,640,CV_32F);
}

Image::~Image()
{
    delete this;
}

void Image::printImageMatrix()
{
}