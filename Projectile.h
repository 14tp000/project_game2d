//
// Created by Jeremi on 17.05.2024.
//

#ifndef PROJECT_GAME2D_PROJECTILE_H
#define PROJECT_GAME2D_PROJECTILE_H

#include "SFML/Graphics.hpp"

class Projectile {
public:
    float speed;
    sf::Vector2f direction;
    float radius;
    sf::CircleShape gfx;
    sf::Vector2f position;
    sf::Vector2f playerPos;
    bool isKilled;
    bool canDamage;
    Projectile(float spd, sf::Vector2f dir, float rad, sf::Vector2f startPos, sf::Vector2f playerPos){
        speed = spd;
        direction = dir;
        radius = rad;
        position = startPos;
        gfx = sf::CircleShape(radius, 12);
        gfx.setPosition(startPos-sf::Vector2f(radius, radius)+playerPos);
        isKilled = false;
        canDamage = true;
    }
    void Update();
    sf::Vector2f getScreenPos();
    sf::Vector2f getGlobalPos();
    void setPosition(sf::Vector2f pos){
        position = pos;
    }
};


#endif //PROJECT_GAME2D_PROJECTILE_H
