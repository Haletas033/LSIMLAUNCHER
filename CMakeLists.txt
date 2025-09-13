cmake_minimum_required(VERSION 3.31)
project(LSIMLAUNCHER)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)

set(IMGUI_SOURCES
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(LSIMLAUNCHER src/main.cpp ${IMGUI_SOURCES}
        src/gui.cpp
        include/gui.h)

target_include_directories(LSIMLAUNCHER PRIVATE
        external/glad/include
        external/glfw/include
        external/
        external/imgui
        external/imgui/backends
)

target_link_libraries(LSIMLAUNCHER PRIVATE glfw glad)