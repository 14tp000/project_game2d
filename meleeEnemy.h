//
// Created by Jeremi on 24.05.2024.
//

#ifndef PROJECT_GAME2D_MELEEENEMY_H
#define PROJECT_GAME2D_MELEEENEMY_H
#include "Enemy.h"
#include "renderManager.h"

class meleeEnemy: public Enemy{
public:
    void damagePlayer(float ammount) override;
    meleeEnemy(sf::Vector2f startPos, float rad, sf::Image* collMap, Player* pl, float hp, renderManager* rM, float speed, scoreManager* sM):
    Enemy(startPos,rad,collMap,pl,hp,rM,speed,1,sM){};
};


#endif //PROJECT_GAME2D_MELEEENEMY_H
