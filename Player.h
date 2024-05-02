//
// Created by Jeremi on 25.04.2024.
//

#ifndef PROJECT_GAME2D_PLAYER_H
#define PROJECT_GAME2D_PLAYER_H


#include "maps/Map.h"

class Player {

private:
    sf::Vector2f position;
    sf::CircleShape shape;
    float radius = 50;
public:
    sf::Image collMap;
    Player(float x, float y, sf::Image collMap){
        shape = sf::CircleShape(radius,32);
        shape.setFillColor(sf::Color::Red);
        position = sf::Vector2f(x,y);
        this->collMap = collMap;
    }
    bool isIn(sf::Vector2f point);
    void update();
    void shunt(int rayNum, float shuntDist);
    void moveDir(sf::Vector2f dir);
    sf::CircleShape getShape();
    sf::Vector2f getPosition();
};


#endif //PROJECT_GAME2D_PLAYER_H
