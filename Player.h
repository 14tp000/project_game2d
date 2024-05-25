//
// Created by Jeremi on 25.04.2024.
//

#ifndef PROJECT_GAME2D_PLAYER_H
#define PROJECT_GAME2D_PLAYER_H


#include "maps/Map.h"
#include "renderManager.h"

class Player {

private:
    sf::Vector2f position;
    sf::CircleShape shape;
    float maxHP;
    float currentHP;
public:
    sf::Image collMap;
    float radius = 50;
    renderManager* renderM;

    Player(float x, float y, sf::Image collMap, float mHP, renderManager* rM){
        shape = sf::CircleShape(radius,32);
        shape.setFillColor(sf::Color::Red);
        position = sf::Vector2f(x,y);
        this->collMap = collMap;
        maxHP = mHP;
        currentHP = maxHP;
        renderM = rM;
    }
    bool isIn(sf::Vector2f point);
    void update();
    void shunt(int rayNum, float shuntDist);
    void moveDir(sf::Vector2f dir);
    sf::CircleShape getShape();
    sf::Vector2f getPosition(){
        return position+sf::Vector2f(radius, radius);
    }
    sf::Vector2f getScreenPosition(){
        return sf::Vector2f(1920/2, 1080/2);
    }
    float getMaxHP(){return maxHP;}
    float getCurrentHp(){return currentHP;}
    sf::Vector2f getScreenPos(){return sf::Vector2f(1920/2,1080/2);}
    void addCurrentHP(float ammount){currentHP+=ammount; if(currentHP>maxHP){currentHP = maxHP;}}
    void damage(float ammount);
    void die();
};


#endif //PROJECT_GAME2D_PLAYER_H
