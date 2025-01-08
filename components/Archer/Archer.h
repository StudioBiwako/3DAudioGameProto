/**
 * @file Archer.h
 * @author Devendra Tambat
 *
 *
 */

#ifndef INC_8_72_COMPONENTS_ARCHER_ARCHER_H
#define INC_8_72_COMPONENTS_ARCHER_ARCHER_H

class Archer
{
private:
    int health = 10;
    int damageReceived = 0;
    bool isFiring = false;
    bool isDrawingBack();
    /*
     * everything needs to be moved to these archers, each archer should be the
     * parent class of an imgui, window, and renderer component...and honestly should play
     * it's own audio files
     * */
public:
    void setIsFiring();
    void setIsDrawingBack();
};

#endif //INC_8_72_COMPONENTS_ARCHER_ARCHER_H
