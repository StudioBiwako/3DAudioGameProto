/**
 * @file Archer.h
 * @author Devendra Tambat
 *
 *
 */

#ifndef INC_8_72_COMPONENTS_ARCHER_ARCHER_H
#define INC_8_72_COMPONENTS_ARCHER_ARCHER_H

#include "../AudioEngine/AudioEngine.h"
#include "../Window/Window.h"

class Archer
{
private:
    int _health = 10;
    Window *_ArcherWindow;
    AudioEngine _AudioEngine;
    std::string _title;
public:
    struct archerLoactionData{
        int x;
        int y;
    };
    Archer(int width, int height,  const char *title, AudioEngine &audio);
    void SetArcherWindowPosition(int x, int y);
    void DisplayArcherWindow();
    void HideArcherWindow();
    int GetHealth();
    bool TakeDamage();
    void PlayAudio();
    void Update();
    void checkHealth();
    Window * GetWindow();
    archerLoactionData ArcherLocation() const;
};

#endif //INC_8_72_COMPONENTS_ARCHER_ARCHER_H
