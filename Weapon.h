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

class Weapon {
public:
    std::vector<Enemy*> enemies;
    float damage;
    float attackCd;
    float range;
    sf::Vector2f center;
    virtual void hit();
    sf::CircleShape attackGfx;
    Player* player;
    float dt;
    void add(Enemy* enm){
        enemies.push_back(enm);
    }
    void remove(){
        enemies.pop_back();
    }
    Weapon(float dmg, float rn, sf::Vector2f cnt, float cd, Player& plr){
        damage = dmg;
        center = cnt;
        attackCd = cd;
        range = rn;
        attackGfx = sf::CircleShape(range, 32);
        player = &plr;
    }
};


#endif //PROJECT_GAME2D_WEAPON_H