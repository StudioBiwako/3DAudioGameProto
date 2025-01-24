// main.cpp
#define GL_SILENCE_DEPRECATION

#include "components/Window/Window.hpp"
#include "components/GUI/GUI.hpp"
#include "components/Renderer/Renderer.hpp"
#include "components/AudioEngine/AudioEngine.hpp"
#include "components/Archer/Archer.hpp"
#include "components/Player/Player.hpp"
#include <iostream>
#include <vector>

int main()
{
    bool gameIsRunning = true;
    try
    {
        AudioEngine audio;
        if (!audio.loadSound("forest", "../Audio/forest.wav"))
        {
            std::cerr << "Failed to load forest sound" << std::endl;
            return 0;
        }
        if (!audio.loadSound("c_piano", "../Audio/c_piano.wav"))
        {
            std::cerr << "Failed to load c_piano sound" << std::endl;
            return 0;
        }
        if (!audio.loadSound("d_piano", "../Audio/c_piano.wav"))
        {
            std::cerr << "Failed to load d_piano sound" << std::endl;
            return 0;
        }

        if (!audio.loadSound("e_piano", "../Audio/c_piano.wav"))
        {
            std::cerr << "Failed to load e_piano sound" << std::endl;
            return 0;
        }

        if (!audio.loadSound("f_piano", "../Audio/c_piano.wav"))
        {
            std::cerr << "Failed to load f_piano sound" << std::endl;
            return 0;
        }

        audio.playSound("forest", true);
        audio.setListenerPosition(0.0f, 0.0f, 0.0f);
        audio.printSoundNames();

        audio.setSoundPosition("c_piano", 0.0f, 0.0f, 5.0f);
        audio.setSoundVolume("c_piano", 1.0f);
        audio.playSound("c_piano", true);

        audio.setSoundPosition("d_piano", 3.0f, 0.0f, 0.0f);
        audio.setSoundVolume("d_piano", 1.0f);
        audio.setSoundPitch("d_piano", 0.5f);
        audio.playSound("d_piano", true);

        audio.setSoundPosition("e_piano", -3.0f, 0.0f, 0.0f);
        audio.setSoundVolume("e_piano", 1.0f);
        audio.setSoundPitch("e_piano", 1.5f);
        audio.playSound("e_piano", true);

        audio.setSoundPosition("f_piano", 0.0f, 0.0f, -5.0f); // Behind (negative Z)
        audio.setSoundVolume("f_piano", 1.0f);
        audio.setSoundPitch("f_piano", 2.0f); // Different pitch to distinguish it
        audio.playSound("f_piano", true);

        std::vector<std::unique_ptr<Archer>> archers;

        // Create archers
        archers.push_back(std::make_unique<Archer>(200, 200, "Archer 1", audio));
        archers.push_back(std::make_unique<Archer>(200, 200, "Archer 2",audio));
        archers.push_back(std::make_unique<Archer>(200, 200, "Archer 3",audio));

        Player newPlayer = Player();
        // Main game loop (must run on main thread for GLFW/OpenGL)
        while (gameIsRunning)
        {
            // Update all archers
            for (auto &archer : archers)
            {
                if (archer->isAlive())
                {
                    if (archer->shouldClose())
                    {
                        //currently closing all archers
                        gameIsRunning = false;
                        break;
                    }
                    archer->update();
                    newPlayer.update();
                }
            }
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}