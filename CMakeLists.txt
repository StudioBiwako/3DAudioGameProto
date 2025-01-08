cmake_minimum_required(VERSION 3.0)
project(8.72)

set(CMAKE_CXX_STANDARD 17)

file(GLOB IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

file(GLOB COMPONENT_SOURCES
    ${CMAKE_SOURCE_DIR}/components/GUI/*.cpp
    ${CMAKE_SOURCE_DIR}/components/Renderer/*.cpp
    ${CMAKE_SOURCE_DIR}/components/Window/*.cpp
    ${CMAKE_SOURCE_DIR}/components/AudioEngine/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/imgui/backends)
include_directories(${CMAKE_SOURCE_DIR}/dr_wav)
include_directories(${CMAKE_SOURCE_DIR}/components)

add_executable(8.72 main.cpp ${COMPONENT_SOURCES} ${IMGUI_SOURCES}
        components/Archer/Archer.cpp
        components/Archer/Archer.h)

find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(8.72 OpenAL::OpenAL OpenGL::GL glfw)