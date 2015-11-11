#pragma once

#include <wx/dir.h>
#include <vector>
#include "Image.h"
#include "Directory.h"

using namespace std;

class ImageManager {

public:
    ImageManager(string trainPath, string testPath);
    vector<Mat> getOpenCVTrainImages();
    vector<Image> getTrainImages();
    vector<int> getTrainLabels();

    vector<Mat> getOpenCVTestImages();
    vector<Image> getTestImages();
    vector<int> getTestLabels();

private:
    void readDirectories();

    vector<Mat> listOfOpenCVTrainImages;
    vector<Image> listOfTrainImages;
    vector<int> listOfTrainLabels;

    vector<Mat> listOfOpenCVTestImages;
    vector<Image> listOfTestImages;
    vector<int> listOfTestLabels;

    Directory trainDirectory;
    Directory testDirectory;
};