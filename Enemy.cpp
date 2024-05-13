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

bool Enemy::inLOS(sf::Vector2f from, sf::Vector2f to){
    sf::Vector2f clock = sf::Vector2f(1,0);
    int successPts = 0;
    int numPts = 5;
    for(int i = 0;i<numPts;i++) {
        sf::Vector2f newClock = vmath::rotateVector(clock, 2 * M_PI / numPts * i) * radius;
        int ptInLOS = 1;
        for (int iter = 0; iter < 400; iter++) {
            sf::Vector2f checkPos = from+newClock - (from+newClock - to) * (iter / 400.f);

            if (Enemy::isIn(checkPos - playerPos)) {
                ptInLOS = 0;
                break;
            }
        }
        successPts+=ptInLOS;
    }
    return successPts>=4;
}


void Enemy::MovePosition(sf::Vector2f pos, float spd) {
    sf::Vector2f dir = vmath::normaliseVector(position+playerPos-pos+sf::Vector2f(radius,radius));
    position-=dir*spd*dt;
}


bool Enemy::moveToNearLOSPoint(sf::Vector2f pos) {
    float minDist = 150;
    float distanceStep = 10;
    int angleDiv = 15;
    int distanceDiv = 10;

    sf::Vector2f clock = sf::Vector2f(1,0);
    float minD = 100000000.f;
    sf::Vector2f out;
    bool morbius = false;
    for (int i = 0; i < distanceDiv; ++i) {
        for (int j = 0; j < angleDiv; ++j) {
            sf::Vector2f newClock = vmath::rotateVector(clock, 2*M_PI/angleDiv*j);
            newClock = newClock*(minDist+distanceStep*i);
            //sf::Vector2f(1920/2,1080/2)
            if(inLOS(position+playerPos+sf::Vector2f(radius,radius),pos+newClock)&&inLOS(sf::Vector2f(1920/2,1080/2),pos+newClock)){
                //debugGfx.setPosition(newClock+pos+sf::Vector2f(-30,-30));
                morbius = true;
                float d = vmath::distV(position+playerPos+sf::Vector2f(radius,radius),newClock+pos);
                out = newClock+pos;
//                if(d<minDist){
//                    minD = d;
//                    out = newClock+pos;
//                }
            }
        }
    }
    if(morbius) {
        MovePosition(out, speed);
    }
    return morbius;
}

void Enemy::shunt(int rayNum, float shuntDist){
    sf::Vector2f newCenter = position+playerPos+sf::Vector2f(radius,radius);

    sf::Vector2f clock = sf::Vector2f(1,0);
    for(int i = 0;i<rayNum;i++){
        if(isIn(newCenter + vmath::rotateVector(clock, 2 * M_PI / rayNum * i) * radius- playerPos)){
            position-=vmath::rotateVector(clock,2*M_PI/rayNum*i)*radius*shuntDist;
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
        if(inLOS(position+playerPos+sf::Vector2f(radius,radius),sf::Vector2f(1920/2,1080/2))) {
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