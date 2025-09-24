cmake_minimum_required(VERSION 3.10)
project(showcaseScene)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${LSIM_PATH} LSIM_build)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

if(NOT PROJECT_SOURCES)
    message(STATUS "No source files found, will run LSIM engine directly")
else()
    add_executable(showcaseScene ${PROJECT_SOURCES})
    target_link_libraries(showcaseScene PRIVATE LSIMLib)
    target_compile_definitions(showcaseScene PRIVATE GAME=1)
endif()
