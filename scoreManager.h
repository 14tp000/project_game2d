//
// Created by Jeremi on 14.06.2024.
//

#ifndef PROJECT_GAME2D_SCOREMANAGER_H
#define PROJECT_GAME2D_SCOREMANAGER_H
#include "SFML/Graphics.hpp"
#include "iostream"
#include "renderManager.h"

class scoreManager {
public:
    sf::Text gfx;
    int score = 0;
    renderManager* rM;
    scoreManager(sf::Vector2f pos, float scale, renderManager* renderManager){
        sf::Font* arial = new sf::Font();

        if (!arial->loadFromFile("..\\assets\\fonts\\arial.ttf"))
        {
            std::cerr<<"Font is dead";
        }

        gfx.setString(std::to_string(score));
        gfx.setFont(*arial);
        gfx.setPosition(pos);
        gfx.setCharacterSize(scale);
        gfx.setFillColor(sf::Color::Red);
        rM = renderManager;
    }

    void addScore(int ammount){
        score+=ammount;
    }

    void UpdateAndDraw(){
        gfx.setString(std::to_string(score));
        rM->addGUI(&gfx);
    }
};


#endif //PROJECT_GAME2D_SCOREMANAGER_H
