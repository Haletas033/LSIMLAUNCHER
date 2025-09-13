#include <filesystem>
#include <iostream>

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



    std::string path = FileIO::LoadWorkingPath("settings.ini");
    if (path.empty()) {
        path = FileIO::GetWorkingPath();
        FileIO::SaveWorkingPath("settings.ini", path.c_str());
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

        Gui::BeginProjects(path);

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_directory(entry.status())) {
                Gui::DrawProject(entry.path().filename().string(), path + entry.path().filename().string());
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