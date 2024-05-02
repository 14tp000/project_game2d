//
// Created by Jeremi on 25.04.2024.
//
#include <SFML/Window.hpp>
#include <cmath>
#include "vmath.h"

sf::Vector2f vmath::rotateVector(sf::Vector2f v, float angle){
    //https://en.wikipedia.org/wiki/Rotation_matrix about rotation matrix
    return sf::Vector2f(v.x* cosf(angle)-v.y*sinf(angle), v.x*sinf(angle)+v.y*cosf(angle));
}

float vmath::vectorMagnitude(sf::Vector2f v){
    return (float)sqrt(v.x*v.x+v.y*v.y);
}


sf::Vector2f vmath::normaliseVector(sf::Vector2f v){
    float magnitude = vectorMagnitude(v);
    if(magnitude!=0) {
        return sf::Vector2f(v.x / magnitude, v.y / magnitude);
    }
    else{
        return  sf::Vector2f(0,0);
    }
}