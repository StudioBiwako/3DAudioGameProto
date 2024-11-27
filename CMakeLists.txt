cmake_minimum_required(VERSION 3.0)
project(ImGuiExample)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/imgui/backends)

# Add executable
add_executable(ImGuiExample main.cpp GUI.cpp Renderer.cpp Window.cpp ${IMGUI_SOURCES})

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(ImGuiExample OpenGL::GL glfw)
