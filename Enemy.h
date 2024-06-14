//
// Created by Jeremi on 11.05.2024.
//

#ifndef PROJECT_GAME2D_ENEMY_H
#define PROJECT_GAME2D_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Destructible.h"
#include "iostream"
#include "renderManager.h"

class Enemy: public Destructible{
    public:
        sf::CircleShape gfx;
        sf::Vector2f position;
        float speed;
        float radius;
        float aggroRadius = 700.f;
        float dt = 1;
        float knockbackForce;
        sf::Image* collMap; //TODO: zrobić lepiej
        Player* player;
        bool inPlayerLOS = false;
        renderManager* renderM;

        virtual void Update();
        bool inLOS(sf::Vector2f from, sf::Vector2f to);
        void MoveScreenPosition(sf::Vector2f pos,float spd);
        void MoveGlobalPosition(sf::Vector2f pos, float spd);
        bool moveToNearLOSPoint(sf::Vector2f pos);
        virtual void MoveToPlayer();
        bool isIn(sf::Vector2f point);
        void shunt(int rayNum, float shuntDist);
        bool collides(sf::Vector2f pt);
        void knockBack(sf::Vector2f dir, float force);
        virtual void damagePlayer(float ammount){std::cout<<"to nie powinno byc wywolywane";}
        sf::Vector2f getScreenPos();
        sf::Vector2f getGlobalPos();
        Enemy(sf::Vector2f startPos, float rad, sf::Image* collMap, Player* pl, float hp, renderManager* rM, float spd, float kbForce, scoreManager* scoreManager){
            radius = rad;
            position = startPos;
            gfx = sf::CircleShape(rad, 32);
            this->collMap = collMap;
            player = pl;
            maxHP = hp;
            currentHP = maxHP;
            renderM = rM;
            speed = spd;
            knockbackForce = kbForce;
            sM = scoreManager;
        }
};


#endif //PROJECT_GAME2D_ENEMY_H
