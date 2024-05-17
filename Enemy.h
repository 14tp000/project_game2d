//
// Created by Jeremi on 11.05.2024.
//

#ifndef PROJECT_GAME2D_ENEMY_H
#define PROJECT_GAME2D_ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
    public:
        sf::CircleShape gfx;
        sf::Vector2f position;
        sf::Vector2f playerPos;
        float speed = 450.f;
        float radius;
        float aggroRadius = 700.f;
        float dt = 1;
        sf::Image collMap; //TODO: zrobić lepiej

        void Update(sf::Vector2f playerP);
        bool inLOS(sf::Vector2f from, sf::Vector2f to);
        void MovePosition(sf::Vector2f pos,float spd);
        bool moveToNearLOSPoint(sf::Vector2f pos);
        void MoveToPlayer();
        bool isIn(sf::Vector2f point);
        void shunt(int rayNum, float shuntDist);
        bool collides(sf::Vector2f pt);
        void knockBack(sf::Vector2f dir, float force);
        sf::Vector2f getScreenPos();
        sf::Vector2f getGlobalPos();
        Enemy(sf::Vector2f startPos, float rad, sf::Image collMap){
            radius = rad;
            position = startPos;
            gfx = sf::CircleShape(rad, 32);
            this->collMap = collMap;
        }
};


#endif //PROJECT_GAME2D_ENEMY_H
