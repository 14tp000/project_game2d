//
// Created by Jeremi on 28.05.2024.
//

#ifndef PROJECT_GAME2D_BOSS_H
#define PROJECT_GAME2D_BOSS_H
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include "vector"

class attackMove {
    attackMove *next;
public:
    float duration;
    float counter = 0;
    Enemy *boss;
    bool finished = false;
    renderManager *rM;

    virtual void attackPlayer() = 0;

    attackMove(attackMove *nxt, float dur, renderManager *renderM) {
        next = nxt;
        duration = dur;
        rM = renderM;
    }

    attackMove *getNext() { return next; }

    void setBoss(Enemy *bss) { boss = bss; }

    void setNext(attackMove *atk) { next = atk; }

    void Reset() {
        counter = 0;
        finished = false;
    }

    virtual void Render() =0;
};

class attack1: public attackMove{
public:
    void attackPlayer() override;
    void Render() override;
    attack1(attackMove* nxt,renderManager* renderM): attackMove(nxt, 2.f,renderM){};
};

class attack2: public attackMove{
public:
    void attackPlayer() override;
    void Render() override;
    attack2(attackMove* nxt,renderManager* renderM): attackMove(nxt,4.f, renderM){};
};


class Boss: public Enemy {
    std::vector<sf::Vector2f>* patrolPts;
    int i = 0;
    float attackDist;
    attackMove* attack;
public:
    Boss(sf::Vector2f startPos, float rad, sf::Image* collMap, Player* pl, float hp, renderManager* rM, float speed, std::vector<sf::Vector2f>* points, float atkDist, attackMove* atk):
    Enemy(startPos,rad,collMap,pl,hp,rM,speed){
        gfx.setFillColor(sf::Color::Magenta);
        patrolPts = points;
        attackDist = atkDist;
        attack = atk;
    };
    void MoveToPlayer() override;
    void damagePlayer(float ammount) override;
};


#endif //PROJECT_GAME2D_BOSS_H
