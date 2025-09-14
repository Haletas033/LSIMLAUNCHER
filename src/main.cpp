#include <filesystem>
#include <iostream>
#include <cstdlib>

#include "../external/glad/include/glad/glad.h"
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"

#include "../include/gui.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "L-SIM LAUNCHER", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    //Get the LSIM directory
    std::string LSIMPath = FileIO::LoadFromini("settings.ini", "LSIM-path");
    if (LSIMPath.empty()) {
        LSIMPath = FileIO::GetDirectory("Select the directory the contains LSIM.exe");
        FileIO::SaveToini("settings.ini", LSIMPath.c_str(), "LSIM-path");
    }

    //Get the working directory
    std::string workingPath = FileIO::LoadFromini("settings.ini", "working-path");
    if (workingPath.empty()) {
        workingPath = FileIO::GetDirectory("Select the directory where you want to store your projects");
        FileIO::SaveToini("settings.ini", workingPath.c_str(), "working-path");
    }

    Gui::Init(window);

    while (!glfwWindowShouldClose(window)) {
        //Get current size of window
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        Gui::width = width;
        Gui::height = height;

        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        Gui::Begin();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(width, height));

        Gui::BeginProjects(workingPath);

        for (const auto& entry : std::filesystem::directory_iterator(workingPath)) {
            if (std::filesystem::is_directory(entry.status())) {
                Gui::DrawProject(entry.path().filename().string(), workingPath + entry.path().filename().string(), LSIMPath);
            }
        }

        ImGui::End();

        Gui::End();

        glfwSwapBuffers(window);
    }
    Gui::CleanUp();
    glfwTerminate();

    return 0;
}