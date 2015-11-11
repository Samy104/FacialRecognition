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
        Image tempImg(temp);
        listOfTrainImages.push_back(tempImg);
        listOfOpenCVTrainImages.push_back(tempImg.getOpenCVMatrix());
        listOfTrainLabels.push_back(count);
        count++;
    }
    count = 0;
    for(wxString filepath : testDirectory.getAvailableFiles())
    {
        string temp = filepath.ToStdString();
        Image tempImg(temp);
        listOfTestImages.push_back(tempImg);
        listOfOpenCVTestImages.push_back(tempImg.getOpenCVMatrix());
        listOfTestLabels.push_back(count);
        count++;
    }

}

vector<Image> ImageManager::getTrainImages()
{
    return this->listOfTrainImages;
}

vector<int> ImageManager::getTrainLabels()
{
    return this->listOfTrainLabels;
}

vector<Mat> ImageManager::getOpenCVTrainImages()
{
    return this->listOfOpenCVTrainImages;
}

vector<Image> ImageManager::getTestImages()
{
    return this->listOfTestImages;
}

vector<int> ImageManager::getTestLabels()
{
    return this->listOfTestLabels;
}

vector<Mat> ImageManager::getOpenCVTestImages()
{
    return this->listOfOpenCVTestImages;
}
