//
// Created by halet on 9/13/2025.
//

#ifndef FILEIO_H
#define FILEIO_H
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

#include <vector>
#include <filesystem>

class FileIO {
public:
    static std::string GetDirectory(const char* prompt);
    static void SaveToini(const std::string &config, const char *path, const char* item);
    static std::string LoadFromini(const std::string &config, const char* item);
    static void MakeProject(const char* path);
    static void LoadProject();
    static void DeleteProject(const char *path);
};

#endif //FILEIO_H
