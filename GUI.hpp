#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class GUI
{
public:
    GUI(GLFWwindow *window);
    ~GUI();

    void newFrame();
    void render();
    void setupUI();

private:
    GLFWwindow *window;
    float sliderValue;
    int counter;
    char inputText[128];
    bool checkbox;
};