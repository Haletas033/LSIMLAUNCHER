//
// Created by halet on 9/13/2025.
//

#include "../include/fileIO.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

std::string FileIO::GetDirectory(const char* prompt) {
    HWND hwnd = nullptr;

    BROWSEINFO bi = {nullptr};
    bi.lpszTitle = prompt;
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

void FileIO::SaveToini(const std::string& config, const char* path, const char* item) {
    std::ifstream in(config);
    std::vector<std::string> lines;
    std::string line;
    bool foundSection = false;
    bool replaced = false;

    while (std::getline(in, line)) {
        if (line == "[file-settings]") {
            foundSection = true;
            lines.push_back(line);
            continue;
        }
        if (foundSection && line.rfind(item, 0) == 0) {
            line = std::string(item) + "=" + path;
            replaced = true;
        }
        lines.push_back(line);
    }
    in.close();

    if (!replaced) {
        if (!foundSection) {
            lines.emplace_back("[file-settings]");
        }
        lines.push_back(std::string(item) + "=" + path);
    }

    std::ofstream out(config);
    for (auto& l : lines) {
        out << l << "\n";
    }
}

std::string FileIO::LoadFromini(const std::string &config, const char* item) {
    std::ifstream in(config);
    std::string line, path;

    if (!in) {
        std::cerr << "Couldn't find file";
        return "";
    }

    while (std::getline(in, line)) {
        if (line.rfind(item + std::string("="), 0) == 0) {
            path = line.substr(std::strlen(item) + 1);
            break;
        }
    }
    return path;
}

void FileIO::MakeProject(const char* path) {
    std::filesystem::create_directory(path);
        std::filesystem::create_directory(path + std::string("/shaders"));
            std::filesystem::copy_file("projectFiles/shaders/default.vert", path + std::string("/shaders/default.vert"));
            std::filesystem::copy_file("projectFiles/shaders/default.frag", path + std::string("/shaders/default.frag"));
            std::filesystem::copy_file("projectFiles/shaders/default.geom", path + std::string("/shaders/default.geom"));
            //Instance
            std::filesystem::copy_file(("projectFiles/shaders/instance.vert"), path + std::string("/shaders/instance.vert"));
            //Skybox
            std::filesystem::copy_file("projectFiles/shaders/skybox.vert", path + std::string("/shaders/skybox.vert"));
            std::filesystem::copy_file("projectFiles/shaders/skybox.frag", path + std::string("/shaders/skybox.frag"));
        //Resources dir
        std::filesystem::create_directory(path + std::string("/resources"));
        //Config
        std::filesystem::create_directory(path + std::string("/config"));
            std::filesystem::copy_file("projectFiles/config/config.json", path + std::string("/config/config.json"));
        //Scripts dir
        std::filesystem::create_directory(path + std::string("/scripts"));
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


