//
// Created by halet on 9/13/2025.
//

#include "../include/gui.h"

#include <iostream>

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

void Gui::BeginProjects(const std::string &path) {
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

    static bool shouldOpenPopup = false;

    if (ImGui::Button("New Project")) {
        shouldOpenPopup = true;
    }

    if (shouldOpenPopup) {
        ImGui::Begin("New Project", &shouldOpenPopup);
        static char buffer[256] = "";
        ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer));

        if (ImGui::Button("Create Project")) {
            FileIO::MakeProject((path + buffer).c_str());
            shouldOpenPopup = false;

            //Clear the buffer
            for (char & i : buffer)
                i = *"";
        }
        ImGui::End();
    }
}


void Gui::DrawProject(const std::string &projectName, const std::string &projectPath, const std::string &LSIMPath) {
    //Get the top-left corner of this project's box
    ImVec2 box_start = ImGui::GetCursorScreenPos();
    box_start.x -= padding;
    box_start.y -= padding;

    ImGui::BeginGroup();

    //Button to load project
    if (ImGui::Button(projectName.c_str())) {
        std::filesystem::current_path(LSIMPath);
        const std::string cmd = "LSIM.exe \"" + projectPath + "\"";
        system(cmd.c_str());
    }

    //Button for run project on same line as load project
    ImGui::SameLine();

    if (ImGui::Button(("Run##" + projectPath).c_str())) {
        std::filesystem::current_path(LSIMPath);
        std::filesystem::current_path(std::filesystem::current_path() / "..");

        std::filesystem::create_directory(projectName);

        system(("cmake -S . -B " + projectName + " -G Ninja -DGAME=ON -DSCRIPTS=" + projectPath + "/scripts").c_str());

        std::filesystem::current_path(std::filesystem::current_path() / projectName);

        system("ninja");

        const std::string cmd = "LSIM.exe \"" + projectPath + "\"";
        system(cmd.c_str());
    }

    //Button for delete project on same line as load project
    ImGui::SameLine();

    ImGui::SetCursorPosX((width - 115));

    if (ImGui::Button(("Delete Project##" + projectPath).c_str())) {
        FileIO::DeleteProject(projectPath.c_str());
    }

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
    ImGui::Dummy(ImVec2(0, padding + 2));
}
