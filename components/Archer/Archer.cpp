/**
 * @file Archer.cpp
 * @author Devendra Tambat
 */

#include "Archer.h"
#include <QTimer>
#include <iostream>

Archer::Archer(int width, int height, const char *title, AudioEngine &audio)
{
    _ArcherWindow = new Window(title);
    _AudioEngine = audio;
    _title = title;
    _title.append("_Bow");
    _AudioEngine.loadSound(_title, "../resources/audioFiles/pianoCKey.wav");
    this->DisplayArcherWindow();
}

void Archer::SetArcherWindowPosition(int x, int y)
{
    const int duration_ms = 1000;
    const int steps = 120;
    const int delay_ms = duration_ms / steps;

    int start_x = _ArcherWindow->x();
    int start_y = _ArcherWindow->y();
    int dx = x - start_x;
    int dy = y - start_y;

    QTimer *timer = new QTimer(_ArcherWindow);
    int step = 0;

    QEventLoop::connect(timer, &QTimer::timeout, [=]() mutable
                        {
        if (step >= steps) {
            timer->stop();
            timer->deleteLater();
            _ArcherWindow->move(x, y);  // Ensure final position is exact
            return;
        }
        
        float progress = static_cast<float>(step) / steps;
        
        float arch_height = -100 * (progress * progress - progress); // Max height of 25 pixels
        
        int current_x = start_x + (dx * progress);
        int current_y = start_y + (dy * progress) - arch_height;
        
        _ArcherWindow->move(current_x, current_y);
        step++; });

    timer->start(delay_ms);
}

void Archer::DisplayArcherWindow()
{
    _ArcherWindow->show();
}

void Archer::HideArcherWindow()
{
    _ArcherWindow->hide();
}

bool Archer::TakeDamage()
{
    if (_health <= 0)
    {
        return false;
    }
    else
    {
        _health--;
        return true;
    }
}

int Archer::GetHealth()
{
    return _health;
}

void Archer::PlayAudio()
{
    _AudioEngine.playSound(_title, false);
}

void Archer::checkHealth()
{
    if (this->GetHealth() <= 0)
    {
        _ArcherWindow->hide();
    }
}

void Archer::Update()
{
    this->checkHealth();
    // update check health etc.
}



Archer::archerLoactionData Archer::ArcherLocation() const
{
    archerLoactionData archerLoc;
    archerLoc.x = _ArcherWindow->x();
    archerLoc.y = _ArcherWindow->y();
    return archerLoc;
}