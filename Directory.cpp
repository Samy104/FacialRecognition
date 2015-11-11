#include "Directory.h"

Directory::Directory(string &path)
{
    this->mPath = path;
    this->mDirectory.GetAllFiles(path, &mFiles);
}