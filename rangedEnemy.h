//
// Created by Jeremi on 25.05.2024.
//

#ifndef PROJECT_GAME2D_RANGEDENEMY_H
#define PROJECT_GAME2D_RANGEDENEMY_H
#include "Enemy.h"
#include "Projectile.h"
#include "renderManager.h"
#include "memory"


class rangedEnemy: public Enemy{
    int projectileI = 0;
    int maxNumProjectiles = 3;
public:
    float counter = 0;
    float attackDelay = 0.5;
    std::vector<Projectile*> bullets;
    float stopDist;
    void damagePlayer(float ammount) override;
    void MoveToPlayer() override;
    void Update() override;
    rangedEnemy(sf::Vector2f startPos, float rad, sf::Image* collMap, Player* pl, float hp, float stopD, renderManager* rM, float speed, scoreManager* sM):
    Enemy(startPos,rad,collMap,pl,hp,rM,speed,1, sM){stopDist = stopD;};
};


#endif //PROJECT_GAME2D_RANGEDENEMY_H
