#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <iostream>
#include <QTimer>
#include "Components/Archer/Archer.h"
#include "Components/Player/Player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Player _player;

    AudioEngine _audioEngine;
    // since Background Audio is not mono we can load it in the main.cpp
    _audioEngine.loadSound("forest", "../resources/audioFiles/forestBackgroundMusic.wav");
    _audioEngine.playSound("forest");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int centerY = screenHeight / 2;
    int spacing = screenWidth / 4;
    int startX = (screenWidth / 2) - spacing;

    Archer archerOne(300, 300, "Archer_One", _audioEngine);
    archerOne.SetArcherWindowPosition(startX-150, centerY-150);
    Archer archerTwo(300, 300, "Archer_Two", _audioEngine);
    archerTwo.SetArcherWindowPosition(startX + spacing-150, centerY-350);
    Archer archerThree(300, 300, "Archer_Three", _audioEngine);
    archerThree.SetArcherWindowPosition(startX + (spacing * 2)-150, centerY-150);

    std::vector<Archer> _archers;
    _archers.push_back(archerOne);
    _archers.push_back(archerTwo);
    _archers.push_back(archerThree);
    QTimer updateTimer;

    std::cout << "main gameplay loop running";
    QObject::connect(&updateTimer, &QTimer::timeout, [&_archers]()
                     {
        for(auto& archer : _archers) {
            archer.Update();
        } });

    updateTimer.start(16);

    return QApplication::exec();
}
