//
// Created by Jeremi on 11.05.2024.
//
#include <SFML/Graphics.hpp>
#include "vmath.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>



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

bool Enemy::inLOS(sf::Vector2f point){
    sf::Vector2f center = position+playerPos+sf::Vector2f(radius,radius);
    sf::Vector2f stDest = point;
//    debugGfx.setPosition(center + sf::Vector2f(-30, -30));
//    debugGfx2.setPosition(center-(center-stDest)*0.5f + sf::Vector2f(-30, -30));

    for(int iter = 0;iter<400;iter++){
        sf::Vector2f checkPos = center-(center-stDest)*(iter/400.f);
//        if(iter == 200) {
//            debugGfx2.setPosition(checkPos + sf::Vector2f(-30, -30));
//        }
        if(Enemy::isIn(checkPos-playerPos)){
            return false;
        }
    }
    return true;
}


void Enemy::MovePosition(sf::Vector2f pos, float spd) {
    sf::Vector2f dir = vmath::normaliseVector(position+playerPos-pos+sf::Vector2f(radius,radius));
    position-=dir*spd;
}


bool Enemy::moveToNearLOSPoint(sf::Vector2f pos) {
    float minDist = 50.f;
    float angleStep = 0.1f;
    float distanceStep = 1.f;

    sf::Vector2f clock = sf::Vector2f(minDist,0);
    for (int i = 0; i < 100; ++i) {
        clock = vmath::rotateVector(clock, angleStep);
        clock += vmath::normaliseVector(clock)*distanceStep;
        if(isIn(clock-playerPos)){
            return false;
        }
        if(inLOS(pos+clock)){
            MovePosition(clock+pos, 0.5f);
            return true;
        }
    }
    return false;
}

void Enemy::shunt(int rayNum, float shuntDist){
    sf::Vector2f newCenter = position+playerPos+sf::Vector2f(radius,radius);
    debugGfx.setPosition(newCenter+sf::Vector2f(-30,-30));

    sf::Vector2f clock = sf::Vector2f(1,0);
    for(int i = 0;i<rayNum;i++){
        if(isIn(newCenter + vmath::rotateVector(clock, 2 * M_PI / rayNum * i) * radius)){
            //position+=vmath::rotateVector(clock,2*M_PI/rayNum*i)*radius*shuntDist;
        }
    }
}

void Enemy::MoveToPlayer(){
    sf::Vector2f v = position+playerPos-sf::Vector2f(1920/2,1080/2)+sf::Vector2f(radius,radius);
    float dist = vmath::vectorMagnitude(v);

    if(dist>aggroRadius){
        gfx.setFillColor(sf::Color::Green);
    }
    else if (dist<=aggroRadius)
    {
        if(inLOS(sf::Vector2f(1920/2,1080/2))) {
            gfx.setFillColor(sf::Color::Blue);
            MovePosition(sf::Vector2f(1920/2,1080/2), speed);
        } else{
            if(moveToNearLOSPoint(sf::Vector2f(1920/2,1080/2))) {
                gfx.setFillColor(sf::Color::Yellow);
            }
            else
            {
                gfx.setFillColor(sf::Color::Red);
            }
        }
    }
}