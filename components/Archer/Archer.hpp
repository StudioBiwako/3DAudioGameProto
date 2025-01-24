#pragma once
#include "../Window/Window.hpp"
#include "../GUI/GUI.hpp"
#include "../Renderer/Renderer.hpp"
#include "../AudioEngine/AudioEngine.hpp"
#include <memory>

class Archer
{
private:
    /*
     * Stats
     * */
    int health = 10;
    int damageReceived = 0;
    bool isFiring = false;
    bool isDrawingBack = false;
    std::unique_ptr<Window> window;
    std::unique_ptr<GUI> gui;
    std::unique_ptr<Renderer> renderer;


public:
    Archer(int width, int height, const char *title, AudioEngine &audio);
    ~Archer() = default;
    AudioEngine audioEngineToCall;

    bool isAlive()
    {
        return true;
    };
    void update();
    void shootArrow();
    bool shouldClose() const;
    void makeContextCurrent();
};