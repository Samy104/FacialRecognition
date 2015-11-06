#ifndef __FACRECIMAGE__H__
#define __FACRECIMAGE__H__

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Image{
private:
    string mImagePath;
    /**
     * this instantly crashes when included. even if not used...
     */
    //Mat* mImageMatrix;

public:
    Image(std::string &path);

    void printImageMatrix();
    ~Image();
};

#endif
