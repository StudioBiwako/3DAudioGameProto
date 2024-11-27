#define GL_SILENCE_DEPRECATION

#include "Window.hpp"
#include "GUI.hpp"
#include "Renderer.hpp"
#include <iostream>

int main()
{
    try
    {
        // Create window
        Window window(800, 800, "ImGui + Triangle");

        // Create GUI and Renderer instances
        GUI gui(window.getWindow());
        Renderer renderer;

        // Setup triangle
        renderer.setupTriangle();

        while (!window.shouldClose())
        {
            window.pollEvents();

            // GUI frame
            gui.newFrame();
            gui.setupUI();

            // Rendering
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