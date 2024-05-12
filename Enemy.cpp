//
// Created by Jeremi on 11.05.2024.
//
#include <SFML/Graphics.hpp>
#include "vmath.h"
#include "Enemy.h"
#include <iostream>



void Enemy::Update(sf::Vector2f playerP){
    gfx.setPosition(position+playerPos);
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
    sf::Vector2f center = position+playerPos+sf::Vector2f(radius,radius)-sf::Vector2f(1920/4,1080/4);
    std::cout<<center.x<<" "<<center.y<<"\n";
    sf::Vector2f stDest = sf::Vector2f(1920/2,1080/2);
    for(int iter = 0;iter<400;iter++){
        sf::Vector2f checkPos = center+stDest*(iter/400.f);
        if(Enemy::isIn(checkPos)){
            return false;
        }
    }
    return true;
}


void Enemy::MoveToPlayer(){
    sf::Vector2f v = position+playerPos-sf::Vector2f(1920/2,1080/2)+sf::Vector2f(radius,radius);
    float dist = vmath::vectorMagnitude(v);

    if(dist>aggroRadius||!inLOS()){
        gfx.setFillColor(sf::Color::Green);
    }
    else if (dist<=aggroRadius)
    {
        std::cout<<"ambatukum2\n";
        gfx.setFillColor(sf::Color::Blue);
        sf::Vector2f dir = v;
        dir = vmath::normaliseVector(dir);
        position -= dir * speed;
    }
//    else {
//        std::cout<<"ambatukum2\n";
//        gfx.setFillColor(sf::Color::Blue);
//
//    }
}