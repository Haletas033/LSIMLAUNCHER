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

        Gui::BeginProjects();

        Gui::DrawProject("Test1", "some very very long long file path to this amazing beautiful award winning game");
        Gui::DrawProject("Test2", "some very very long long file path to this amazing beautiful award winning game");
        Gui::DrawProject("Test3", "some very very long long file path to this amazing beautiful award winning game");

        ImGui::End();

        Gui::End();

        glfwSwapBuffers(window);
    }
    Gui::CleanUp();
    glfwTerminate();

    return 0;
}