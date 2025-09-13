//
// Created by halet on 9/13/2025.
//

#include "../include/gui.h"

float Gui::padding = 8.f;
int Gui::width = 800;
int Gui::height = 600;

void Gui::Init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Gui::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::End() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::BeginProjects() {
    ImGui::Begin("Header", nullptr,
            ImGuiWindowFlags_NoTitleBar     |
            ImGuiWindowFlags_NoResize       |
            ImGuiWindowFlags_NoBackground   |
            ImGuiWindowFlags_NoMove         |
            ImGuiWindowFlags_NoCollapse);

    const auto title = "L-SIM LAUNCHER";
    const ImVec2 text_size = ImGui::CalcTextSize(title);

    ImGui::SetCursorPosX((width / 2.f) - text_size.x * 0.5f);
    ImGui::Text("L-SIM LAUNCHER");

    ImGui::Text("Projects");
    ImGui::SameLine();
    ImGui::SetCursorPosX(width - 100);
    ImGui::Button("New Project");
}


void Gui::DrawProject(const std::string &projectName, const std::string &projectPath) {
    //Get the top-left corner of this project's box
    ImVec2 box_start = ImGui::GetCursorScreenPos();
    box_start.x -= padding;
    box_start.y -= padding;

    ImGui::BeginGroup();

    //Button to load project
    ImGui::Button(projectName.c_str());

    //Button to delete project on same line as load project
    ImGui::SameLine();
    ImGui::SetCursorPosX((width - 115));
    ImGui::Button("Delete Project");

    ImGui::Text(projectPath.c_str());

    ImGui::EndGroup();

    //Get the bottom-right corner of this project's box
    ImVec2 box_end = ImGui::GetItemRectMax();
    box_end.x += padding;
    box_end.y += padding;

    //Draw the box around the project
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(
        box_start, box_end,
        IM_COL32(40, 40, 60, 100)
    );

    //Move cursor down for next box
    ImGui::SetCursorPosY(box_end.y + padding);
}
