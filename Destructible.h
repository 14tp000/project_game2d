//
// Created by Jeremi on 24.05.2024.
//

#ifndef PROJECT_GAME2D_DESTRUCTIBLE_H
#define PROJECT_GAME2D_DESTRUCTIBLE_H

#include "scoreManager.h"

class Destructible {
public:
    bool dead = false;
    float currentHP;
    float maxHP;
    int score = 20;

    scoreManager* sM;
    void setHP(float hp){
        currentHP = hp;
    }
    float getHP(){
        return currentHP;
    }
    void damage(float ammount);
    void die(){
        sM->addScore(score);
        dead = true;
    }
};


#endif //PROJECT_GAME2D_DESTRUCTIBLE_H
