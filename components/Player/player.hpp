/**
 * @file Player.hpp
 * @author Devendra Tambat
 *
 *
 */

#ifndef INC_8_72_COMPONENTS_PLAYER_H
#define INC_8_72_COMPONENTS_PLAYER_H

class Player
{
private:
    int health = 10;
    bool isAlive = true;
public:
    int getHealth(){return  health;}
    void takeDamage(){
        health--;
    }
    bool getPlayerStatus(){
        return isAlive;
    }
    void killPlayer(){
        isAlive = false;
    }
    void update(){
        if(this -> getHealth() <= 0){
            isAlive = false;
        }
    }
};

#endif //INC_8_72_COMPONENTS_PLAYER_H
