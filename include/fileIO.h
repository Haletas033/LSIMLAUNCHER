//
// Created by halet on 9/13/2025.
//

#ifndef FILEIO_H
#define FILEIO_H
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <vector>

class FileIO {
public:
    static std::string GetWorkingPath();
    static void SaveWorkingPath(const std::string &config, const char *path);
    static std::string LoadWorkingPath(const std::string &config);
    static void MakeProject(const char* path);
    static void LoadProject();
    static void DeleteProject(const char *path);
};

#endif //FILEIO_H
