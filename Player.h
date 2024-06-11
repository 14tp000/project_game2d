//
// Created by Jeremi on 25.04.2024.
//

#ifndef PROJECT_GAME2D_PLAYER_H
#define PROJECT_GAME2D_PLAYER_H


#include "renderManager.h"
#include "vector"
#include "SFML/Graphics.hpp"

class Player;

class Talisman {
public:
    Player* player;
    bool enabled = true;
    bool active = false;
    float duration;
    float counter;
    float dt;
    sf::RectangleShape gfx;

    Talisman(Player* plr, float dur, sf::Vector2f gfxPos){
        player = plr;
        duration = dur;
        gfx = sf::RectangleShape(sf::Vector2f(50,50));
        gfx.setPosition(gfxPos);
    }
    virtual void Update()=0;
    virtual void Trigger()=0;
    void Enable(){
        enabled = true;
        counter = 0;
    }
};

class Player {

private:
    sf::Vector2f position;
    sf::CircleShape shape;
    float maxHP;
    float currentHP;
public:
    sf::Image collMap;
    float radius = 50;
    float movementSpeed;
    renderManager* renderM;
    std::vector<Talisman*> talismans;

    ////talisman flags
    bool onCrit = false;

    Player(float x, float y, sf::Image collMap, float mHP, renderManager* rM, float spd){
        shape = sf::CircleShape(radius,32);
        shape.setFillColor(sf::Color::Red);
        position = sf::Vector2f(x,y);
        this->collMap = collMap;
        maxHP = mHP;
        currentHP = maxHP;
        renderM = rM;
        movementSpeed = spd;
    }

    void heal(float ammount){
        currentHP+=ammount;
        if(currentHP>maxHP) { currentHP = maxHP;}
    }

    void addTalisman(Talisman* talisman){
        talismans.push_back(talisman);
    }
    void updateTalismans(){
        for(auto talisman: talismans){
            talisman->Update();
        }
        resetFlags();
    }
    void resetFlags(){
        onCrit = false;
    }
    bool isIn(sf::Vector2f point);
    void update();
    void shunt(int rayNum, float shuntDist);
    void moveDir(sf::Vector2f dir);
    sf::CircleShape getShape();
    sf::Vector2f getPosition(){
        return position+sf::Vector2f(radius, radius);
    }
    float getMaxHP(){return maxHP;}
    float getCurrentHp(){return currentHP;}
    sf::Vector2f getScreenPos(){return sf::Vector2f(1920/2,1080/2);}
    void addCurrentHP(float ammount){currentHP+=ammount; if(currentHP>maxHP){currentHP = maxHP;}}
    void damage(float ammount);
    void die();
};


#endif //PROJECT_GAME2D_PLAYER_H
