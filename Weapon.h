//
// Created by Jeremi on 17.05.2024.
//

#ifndef PROJECT_GAME2D_WEAPON_H
#define PROJECT_GAME2D_WEAPON_H

#include <utility>

#include "Enemy.h"
#include "vector"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "renderManager.h"

class Weapon {
public:
    float counter = 0;
    std::vector<Enemy*>* enemies;
    float damage;
    int critChance;
    float critMultiplier;
    float attackCd;
    float range;
    sf::Vector2f center;
    virtual void hit()=0;
    sf::CircleShape attackGfx;
    Player* player;
    float dt;
    renderManager* renderM;
    int critNumber;
    virtual void Update(float dt){
        counter+=dt;
    }
    Weapon(float dmg, int cc, float cm, float rn, float cd, Player* plr, std::vector<Enemy*>* enms, renderManager* rM){
        damage = dmg;
        critChance = cc;
        critMultiplier = cm;
        center = player->getScreenPos();
        attackCd = cd;
        range = rn;
        attackGfx = sf::CircleShape(range, 32);
        player = plr;
        enemies = enms;
        renderM = rM;
    }
};


#endif //PROJECT_GAME2D_WEAPON_H
