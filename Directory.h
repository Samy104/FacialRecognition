#pragma once

#include <wx/dir.h>

using namespace std;

class Directory {
private:
    wxDir mDirectory;
    string mPath;
    wxArrayString mFiles;

public:
    Directory() {}
    Directory(string& path);
    wxArrayString getAvailableFiles()   {return this->mFiles;}
};