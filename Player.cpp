#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "vmath.h"
#include "Player.h"
#include "iostream"



void Player::update(){
    shape.setPosition(1920/2-radius, 1080/2-radius);
    renderM->addObj(&shape);
}
bool Player::isIn(sf::Vector2f point){
    if((int)(collMap.getPixel(point.x, point.y).r) < 50) {
        return false;
    }
    else{
        return true;
    }
}

void Player::damage(float ammount) {
    currentHP-=ammount;
    if(currentHP<=0){
        currentHP = 0;
        die();
    }
}

void Player::die() {
    //std::cout<<"Rip\n";
}

void Player::shunt(int rayNum, float shuntDist){
    sf::Vector2f newPlayerCenter = sf::Vector2f(1920/2-radius, 1080/2-radius)-position;

    sf::Vector2f clock = sf::Vector2f(1,0);
    for(int i = 0;i<rayNum;i++){
        if(isIn(newPlayerCenter + vmath::rotateVector(clock, 2 * M_PI / rayNum * i) * radius)){
            position+=vmath::rotateVector(clock,2*M_PI/rayNum*i)*radius*shuntDist;
        }
    }
}

void Player::moveDir(sf::Vector2f dir){
    position-=dir;
}
sf::CircleShape Player::getShape(){return shape;}


