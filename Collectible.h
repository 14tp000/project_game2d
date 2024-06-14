//
// Created by Jeremi on 11.06.2024.
//

#ifndef PROJECT_GAME2D_COLLECTIBLE_H
#define PROJECT_GAME2D_COLLECTIBLE_H
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "vmath.h"
#include "iostream"

class Collectible {
public:
    Player* player;
    float collectRadius;
    sf::RectangleShape gfx;
    bool collected = false;
    sf::Vector2f position;
    Collectible(Player* plr, float radius, sf::Vector2f pos, sf::Color color){
        player = plr;
        collectRadius = radius;
        position = pos;
        gfx = sf::RectangleShape(sf::Vector2f(50,50));
        gfx.setPosition(position);
        gfx.setFillColor(color);
    }
    virtual void Trigger()=0;
    void Update();
};

class HealCollectible: public Collectible{
public:
    float healAmmount;
    void Trigger();
    HealCollectible(Player* plr, float radius, sf::Vector2f  pos, sf::Color color, float ammount):
            Collectible(plr, radius, pos, color)  {healAmmount = ammount; }
};

class MaxHPUp: public Collectible{
public:
    float boostAmmount;
    void Trigger() override;
    MaxHPUp(Player* plr, float radius, sf::Vector2f  pos, sf::Color color, float ammount):
            Collectible(plr, radius, pos, color)  {boostAmmount = ammount; }
};

class UnlockTalisman: public Collectible{
public:
    void Trigger() override;
    UnlockTalisman(Player* plr, float radius, sf::Vector2f  pos, sf::Color color):
        Collectible(plr, radius, pos, color){};
};

class BossSpawn: public Collectible{
public:
    bool bossSpawned = false;
    void Trigger() override {std::cout<<"Boss Spawned";};
    BossSpawn(Player* plr, float radius, sf::Vector2f  pos, sf::Color color):
    Collectible(plr, radius, pos, color){};
};

#endif //PROJECT_GAME2D_COLLECTIBLE_H
