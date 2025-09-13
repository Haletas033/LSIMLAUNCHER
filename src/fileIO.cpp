//
// Created by halet on 9/13/2025.
//

#include "../include/fileIO.h"

#include <filesystem>
#include <fstream>
#include <iostream>

std::string FileIO::GetWorkingPath() {
    HWND hwnd = nullptr;

    BROWSEINFO bi = {nullptr};
    bi.lpszTitle = "Select the working directory";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.hwndOwner = hwnd;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr) {
        char path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            return {path + std::string("\\")};
        }
    }
    return {};
}


void FileIO::SaveWorkingPath(const std::string &config, const char *path) {
    std::ofstream out(config);
    out << "[file-settings]\n";
    out << "path=" << path << "\n";
}

std::string FileIO::LoadWorkingPath(const std::string &config) {
    std::ifstream in(config);
    std::string line, path;

    if (!in) {
        std::cerr << "Couldn't find file";
        return "";
    }

    while (std::getline(in, line)) {
        if (line.rfind("path=", 0) == 0) {
            path = line.substr(5);
            break;
        }
    }
    return path;
}

void FileIO::MakeProject(const char* path) {
    std::filesystem::create_directory(path);
        std::filesystem::create_directory(path + std::string("/shaders"));
        std::filesystem::create_directory(path + std::string("/resources"));
        std::filesystem::create_directory(path + std::string("/config"));
}

void FileIO::DeleteProject(const char* path) {
    //Convert the path into a wstring
    std::string str(path);
    const std::wstring wpath(str.begin(), str.end());
    std::wstring message = L"Are you sure you want to delete ";
    message += wpath;

    const int result = MessageBoxW(
    nullptr,
    message.c_str(),
    L"Warning",
    MB_YESNO | MB_ICONWARNING
    );


    if (result == IDYES) {
        std::filesystem::remove_all(path);
    }
}


