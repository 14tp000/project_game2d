#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "vmath.h"
#include "Player.h"
#include "./maps/Map.h"
#include "iostream"

void Player::update(){
    shape.setPosition(position);
}
bool Player::isIn(sf::Vector2f point){
    if(collMap.getPixel(point.x, point.y) == sf::Color::Black) {
        return false;
    }
    else{
        return true;
    }
}


void Player::shunt(int rayNum, float shuntDist){
    sf::Vector2f newPlayerCenter = sf::Vector2f(radius, radius)+position;

    sf::Vector2f clock = sf::Vector2f(1,0);
    for(int i = 0;i<rayNum;i++){
        if(isIn(newPlayerCenter + vmath::rotateVector(clock, 2 * M_PI / rayNum * i) * radius)){
            position-=vmath::rotateVector(clock,2*M_PI/rayNum*i)*radius*shuntDist;
        }
    }
}

void Player::moveDir(sf::Vector2f dir){
    position+=dir;
}
sf::CircleShape Player::getShape(){return shape;}
sf::Vector2f Player::getPosition(){return position+sf::Vector2f(radius, radius);}
