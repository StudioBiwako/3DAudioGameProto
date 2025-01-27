/**
 * @file Player.cpp
 * @author Devendra Tambat
 */

#include "Player.h"
bool Player::TakeDamage()
{
    if(_health <= 0){
        return false;
    }
    else{
        _health--;
        return true;
    }
}

int Player::GetHealth(){
    return _health;
}