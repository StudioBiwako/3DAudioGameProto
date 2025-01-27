#pragma once

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl3.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
    Window(int width, int height, const char *title);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    void makeContextCurrent();
    void getFramebufferSize(int &width, int &height);
    GLFWwindow *getWindow() { return window; }

    void clear(float r, float g, float b, float a);

private:
    GLFWwindow *window;
    void initGLFW();
    void setupHints();
    void createWindow(int width, int height, const char *title);
};