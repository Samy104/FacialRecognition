#include "ImageManager.h"

ImageManager::ImageManager(string trainPath, string testPath) : trainDirectory(trainPath), testDirectory(testPath)
{
    this->readDirectories();
}

void ImageManager::readDirectories()
{
    int count = 0;
    for(wxString filepath : trainDirectory.getAvailableFiles())
    {
        string temp = filepath.ToStdString();
        int tempClass = atoi(filepath.ToStdString().substr(filepath.find_last_of("_") + 1, filepath.find_last_of(".")).c_str());
        Image tempImg(temp, CV_LOAD_IMAGE_GRAYSCALE);
        listOfTrainImages.push_back(tempImg);
        listOfOpenCVTrainImages.push_back(tempImg.getOpenCVMatrix());
        listOfTrainLabels.push_back(tempClass);
    }
    for(wxString filepath : testDirectory.getAvailableFiles())
    {
        string temp = filepath.ToStdString();
        int tempClass = atoi(filepath.ToStdString().substr(filepath.find_last_of("_") + 1, filepath.find_last_of(".")).c_str());
        Image tempImg(temp, CV_LOAD_IMAGE_GRAYSCALE);
        listOfTestImages.push_back(tempImg);
        listOfOpenCVTestImages.push_back(tempImg.getOpenCVMatrix());
        listOfTestLabels.push_back(tempClass);
    }

}

vector<Image>* ImageManager::getTrainImages()
{
    return &this->listOfTrainImages;
}

vector<int> ImageManager::getTrainLabels()
{
    return this->listOfTrainLabels;
}

vector<Mat>* ImageManager::getOpenCVTrainImages()
{
    return &this->listOfOpenCVTrainImages;
}

vector<Image>* ImageManager::getTestImages()
{
    return &this->listOfTestImages;
}

vector<int> ImageManager::getTestLabels()
{
    return this->listOfTestLabels;
}

vector<Mat>* ImageManager::getOpenCVTestImages()
{
    return &this->listOfOpenCVTestImages;
}
