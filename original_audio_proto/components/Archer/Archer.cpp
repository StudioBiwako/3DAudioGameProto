/**
 * @file Archer.cpp
 * @author Devendra Tambat
 */

#include "Archer.hpp"

Archer::Archer(int width, int height,  const char *title, AudioEngine &audio)
{

    this->window = std::make_unique<Window>(width, height, title);
    this->window->makeContextCurrent();
    this->gui = std::make_unique<GUI>(window->getWindow());
    this->renderer = std::make_unique<Renderer>();
    this->audioEngineToCall = audio;
    this->renderer->setupTriangle();
    this->renderer->addTriangle(0.0f, 0.0f);
}

void Archer::update()
{
    this->window->makeContextCurrent();
    this->window->pollEvents();
    this->gui->newFrame();
    this->gui->setupUI();

    int display_w, display_h;
    this->window->getFramebufferSize(display_w, display_h);
    glViewport(0, 0, display_w, display_h);
    this->window->clear(0.45f, 0.55f, 0.60f, 1.00f);
    this->renderer->render();
    this->gui->render();
    this->window->swapBuffers();
}

bool Archer::shouldClose() const
{
    return this->window->shouldClose();
}

void Archer::makeContextCurrent()
{
    this->window->makeContextCurrent();
}

void Archer::shootArrow() {
    audioEngineToCall.playSound("c_piano", false);
}