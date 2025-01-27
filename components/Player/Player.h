/**
 * @file Player.h
 * @author Devendra Tambat
 *
 *
 */

#ifndef INC_8_72_COMPONENTS_PLAYER_PLAYER_H
#define INC_8_72_COMPONENTS_PLAYER_PLAYER_H

class Player
{
private:
    int _health = 10;

public:
    int GetHealth();
    bool TakeDamage();
};

#endif //INC_8_72_COMPONENTS_PLAYER_PLAYER_H
