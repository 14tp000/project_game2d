//
// Created by Jeremi on 11.05.2024.
//
#include <SFML/Graphics.hpp>
#include "vmath.h"
#include "Enemy.h"



void Enemy::Update(sf::Vector2f playerP){
    gfx.setPosition(position);
    playerPos = playerP;
}

bool Enemy::isIn(sf::Vector2f point){
    if((int)(collMap.getPixel(point.x, point.y).r) < 50) {
        return false;
    }
    else{
        return true;
    }
}

bool Enemy::inLOS(){
    sf::Vector2f center = position+sf::Vector2f(radius, radius);
    sf::Vector2f stDest = playerPos-center;
    for(int iter = 0;iter<400;iter++){
        sf::Vector2f checkPos = center+stDest*(iter/400.f);
        if(Enemy::isIn(checkPos)){
            return false;
        }
    }
    return true;
}


void Enemy::MoveToPlayer(){
    float dist = vmath::distV(playerPos,position);

    if(dist>aggroRadius||!inLOS()){
        gfx.setFillColor(sf::Color::Green);
    }
    else {
        gfx.setFillColor(sf::Color::Blue);
        sf::Vector2f dir = (position + sf::Vector2f(radius, radius)) - playerPos;
        dir = vmath::normaliseVector(dir);
        position -= dir * speed;
    }
}