//
// Created by halet on 9/13/2025.
//

#ifndef GUI_H
#define GUI_H
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

class Gui {
public:
    static float padding;
    static int width;
    static int height;

    static void Init(GLFWwindow* window);
    static void Begin();
    static void End();
    static void CleanUp();
    static void BeginProjects();
    static void DrawProject(const std::string &projectName, const std::string &projectPath);
};

#endif //GUI_H
