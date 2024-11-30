#define GL_SILENCE_DEPRECATION

#include "components/Window/Window.hpp"
#include "components/GUI/GUI.hpp"
#include "components/Renderer/Renderer.hpp"
#include "components/AudioEngine/AudioEngine.hpp"
#include <iostream>

int main()
{
    try
    {

        AudioEngine audio;

        AudioEngine::printWorkingDirectory();

        // Try to load the sound
        if (!audio.loadSound("forest", "Audio/forest.wav"))
        {
            std::cerr << "Failed to load forest sound" << std::endl;
            return 0;
        }
        // audio.loadSound("background", "Audio/forest.wav");
        //  audio.loadSound("effect", "path/to/effect.wav");

        audio.playSound("forest", true);

        audio.setListenerPosition(0.0, 0.0, 0.0);

        // audio.setSoundPosition("effect", 0.0, 0.0, 0.0);
        // audio.playSound("effect");

        Window window(800, 800, "8.72");

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