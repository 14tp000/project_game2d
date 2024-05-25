//
// Created by Jeremi on 11.05.2024.
//
#include <SFML/Graphics.hpp>
#include "vmath.h"
#include "Enemy.h"
#include <iostream>
#include <cmath>



void Enemy::Update(){
    if(!dead) {
        gfx.setPosition(position + player->getPosition());
        renderM->addObj(&gfx);
    }
}

bool Enemy::isIn(sf::Vector2f point){
    if((int)(collMap->getPixel(point.x, point.y).r) < 50) {
        return false;
    }
    else{
        return true;
    }
}

bool Enemy::collides(sf::Vector2f pt) {
    return vmath::distV(pt, position+player->getPosition()) <=radius;
}

void Enemy::knockBack(sf::Vector2f dir, float force) {
    position-=dir*force;
}

bool Enemy::inLOS(sf::Vector2f from, sf::Vector2f to){
    sf::Vector2f clock = sf::Vector2f(1,0);
    int successPts = 0;
    int numPts = 4;
    for(int i = 0;i<numPts;i++) {
        sf::Vector2f newClock = vmath::rotateVector(clock, 2 * M_PI / numPts * i) * radius;
        int ptInLOS = 1;
        for (int iter = 0; iter < 100; iter++) {
            sf::Vector2f checkPos = from+newClock - (from+newClock - to) * (iter / 100.f);

            if (Enemy::isIn(checkPos - player->getPosition())) {
                ptInLOS = 0;
                break;
            }
        }
        successPts+=ptInLOS;
    }
    return successPts>=3;
}


void Enemy::MovePosition(sf::Vector2f pos, float spd) {
    sf::Vector2f dir = vmath::normaliseVector(position+player->getPosition()-pos+sf::Vector2f(radius,radius));
    position-=dir*spd*dt;
}

sf::Vector2f Enemy::getScreenPos() {
    return position+player->getPosition()+sf::Vector2f(radius, radius);
}

sf::Vector2f Enemy::getGlobalPos() {
    return position+sf::Vector2f(radius,radius);
}

bool Enemy::moveToNearLOSPoint(sf::Vector2f pos) {
    float minDist = 150;
    float distanceStep = 15;
    int angleDiv = 15;
    int distanceDiv = 8;

    sf::Vector2f clock = sf::Vector2f(1,0);
    sf::Vector2f out;
    bool morbius = false;
    for (int i = 0; i < distanceDiv; ++i) {
        for (int j = 0; j < angleDiv; ++j) {
            sf::Vector2f newClock = vmath::rotateVector(clock, 2*M_PI/angleDiv*j);
            newClock = newClock*(minDist+distanceStep*i);
            if(inLOS(position+player->getPosition()+sf::Vector2f(radius,radius),pos+newClock)&&inLOS(sf::Vector2f(1920/2,1080/2),pos+newClock)){
                morbius = true;
                out = newClock+pos;
            }
        }
    }
    if(morbius) {
        MovePosition(out, speed);
    }
    return morbius;
}

void Enemy::shunt(int rayNum, float shuntDist){
    sf::Vector2f newCenter = position+player->getPosition()+sf::Vector2f(radius,radius);

    sf::Vector2f clock = sf::Vector2f(1,0);
    for(int i = 0;i<rayNum;i++){
        if(isIn(newCenter + vmath::rotateVector(clock, 2 * M_PI / rayNum * i) * radius- player->getPosition())){
            position-=vmath::rotateVector(clock,2*M_PI/rayNum*i)*radius*shuntDist;
        }
    }

}
void Enemy::MoveToPlayer(){
    float dist = vmath::distV(player->getScreenPos(),getScreenPos());
    inPlayerLOS = false;
    if(dist>aggroRadius){
        gfx.setFillColor(sf::Color::Green);
    }
    else if (dist<=aggroRadius)
    {
        if(inLOS(position+player->getPosition()+sf::Vector2f(radius,radius),sf::Vector2f(1920/2,1080/2))) {
            inPlayerLOS = true;
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