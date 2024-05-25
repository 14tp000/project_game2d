//
// Created by Jeremi on 24.05.2024.
//

#ifndef PROJECT_GAME2D_DESTRUCTIBLE_H
#define PROJECT_GAME2D_DESTRUCTIBLE_H


class Destructible {
public:
    bool dead = false;
    float currentHP;
    float maxHP;
    void setHP(float hp){
        currentHP = hp;
    }
    float getHP(){
        return currentHP;
    }
    void damage(float ammount);
    void die(){
        dead = true;
    }
};


#endif //PROJECT_GAME2D_DESTRUCTIBLE_H
