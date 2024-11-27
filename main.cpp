#define GL_SILENCE_DEPRECATION

#include "Window.hpp"
#include "GUI.hpp"
#include "Renderer.hpp"
#include <iostream>

int main()
{
    try
    {
        Window window(800, 800, "The Three Blind Archers");

        GUI gui(window.getWindow());
        Renderer renderer;

        renderer.setupTriangle();
        renderer.addTriangle(0.0f, 0.0f);                          // Center triangle
        renderer.addTriangle(0.5f, 0.5f);                          // Top right triangle
        renderer.addTriangle(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f);      // Bottom left green triangle
        renderer.addTriangle(0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.5f); // Bottom right yellow, half size

        while (!window.shouldClose())
        {
            window.pollEvents();

            gui.newFrame();
            gui.setupUI();

            int display_w, display_h;
            window.getFramebufferSize(display_w, display_h);
            glViewport(0, 0, display_w, display_h);

            window.clear(0.45f, 0.55f, 0.60f, 1.00f);

            renderer.render();
            gui.render();

            window.swapBuffers();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}