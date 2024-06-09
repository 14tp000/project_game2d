//
// Created by Jeremi on 28.05.2024.
//

#ifndef PROJECT_GAME2D_BOSS_H
#define PROJECT_GAME2D_BOSS_H
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include "vector"
#include "Projectile.h"
#include "vmath.h"
#include "cmath"
#include "attackMove.h"
#include "memory"


class Boss: public Enemy {
    std::vector<sf::Vector2f>* patrolPts;
    int i = 0;
    float attackDist;
    attackMove* attack;
public:
    std::vector<std::unique_ptr<Projectile>> bullets;
    int projectileI = 0;
    int maxNumProjectile = 100;
    Boss(sf::Vector2f startPos, float rad, sf::Image* collMap, Player* pl, float hp, renderManager* rM, float speed, std::vector<sf::Vector2f>* points, float atkDist, attackMove* atk):
    Enemy(startPos,rad,collMap,pl,hp,rM,speed,0){
        gfx.setFillColor(sf::Color::Magenta);
        patrolPts = points;
        attackDist = atkDist;
        attack = atk;
    };
    void MoveToPlayer() override;
    void damagePlayer(float ammount) override;
};

class attack1: public attackMove{
    float ctr = 0;
    float delay;
    Boss* boss;
    float angleOffset = 0;
    float angleOffsetStep = 1;
public:
    int numBullets;
    float radius;
    void Render() override;
    void attackPlayer() override;
    void setBoss(Boss *bss) { boss = bss; }
    attack1(attackMove* nxt,renderManager* renderM, int numCircles, float rad, float dl, float duration): attackMove(nxt, duration,renderM){
        numBullets = numCircles;
        radius = rad;
        delay = dl;
    };
};

class attack2: public attackMove{
    Boss* boss;
    float radius;
    float activate;
public:
    int numBulletsX;
    int numBulletsY;
    float step;
    void attackPlayer() override;
    void Render() override;
    void setBoss(Boss *bss) { boss = bss; }
    attack2(attackMove* nxt,renderManager* renderM, int numX, int numY, float stp, float rad, float duration, float act): attackMove(nxt,duration, renderM){
        numBulletsX = numX;
        numBulletsY = numY;
        step = stp;
        radius = rad;
        activate = act;
    };
};

class wait: public attackMove{
    Boss* boss;
public:
    void attackPlayer() override;
    void Render() override;
    void setBoss(Boss *bss) { boss = bss; }
    wait(attackMove* nxt,renderManager* renderM,float duration): attackMove(nxt,duration, renderM){};
};
#endif //PROJECT_GAME2D_BOSS_H
