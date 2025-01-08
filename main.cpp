// main.cpp
#define GL_SILENCE_DEPRECATION

#include "components/Window/Window.hpp"
#include "components/GUI/GUI.hpp"
#include "components/Renderer/Renderer.hpp"
#include "components/AudioEngine/AudioEngine.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        AudioEngine audio;
        if (!audio.loadSound("forest", "../Audio/forest.wav")) {
            std::cerr << "Failed to load forest sound" << std::endl;
            return 0;
        }
        audio.playSound("forest", true);
        audio.setListenerPosition(0.0, 0.0, 0.0);
        audio.printSoundNames();

        Window archer1(200, 200, "Archer 1");
        Window archer2(200, 200, "Archer 2");
        Window archer3(200, 200, "Archer 3");

        archer1.makeContextCurrent();
        GUI gui1(archer1.getWindow());

        archer2.makeContextCurrent();
        GUI gui2(archer2.getWindow());

        archer3.makeContextCurrent();
        GUI gui3(archer3.getWindow());

        Renderer renderer1;
        Renderer renderer2;
        Renderer renderer3;

        renderer1.setupTriangle();
        renderer1.addTriangle(0.0f, 0.0f);

        renderer2.setupTriangle();
        renderer2.addTriangle(0.0f, 0.0f);

        renderer3.setupTriangle();
        renderer3.addTriangle(0.0f, 0.0f);

        while (!archer1.shouldClose() && !archer2.shouldClose() && !archer3.shouldClose()) {
            if (!archer1.shouldClose()) {
                archer1.makeContextCurrent();
                archer1.pollEvents();
                gui1.newFrame();
                gui1.setupUI();

                int display_w1, display_h1;
                archer1.getFramebufferSize(display_w1, display_h1);
                glViewport(0, 0, display_w1, display_h1);
                archer1.clear(0.45f, 0.55f, 0.60f, 1.00f);
                renderer1.render();
                gui1.render();
                archer1.swapBuffers();
            }

            if (!archer2.shouldClose()) {
                archer2.makeContextCurrent();
                archer2.pollEvents();
                gui2.newFrame();
                gui2.setupUI();

                int display_w2, display_h2;
                archer2.getFramebufferSize(display_w2, display_h2);
                glViewport(0, 0, display_w2, display_h2);
                archer2.clear(0.55f, 0.45f, 0.60f, 1.00f);
                renderer2.render();
                gui2.render();
                archer2.swapBuffers();
            }

            if (!archer3.shouldClose()) {
                archer3.makeContextCurrent();
                archer3.pollEvents();
                gui3.newFrame();
                gui3.setupUI();

                int display_w3, display_h3;
                archer3.getFramebufferSize(display_w3, display_h3);
                glViewport(0, 0, display_w3, display_h3);
                archer3.clear(0.60f, 0.45f, 0.55f, 1.00f);
                renderer3.render();
                gui3.render();
                archer3.swapBuffers();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}