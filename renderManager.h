//
// Created by Jeremi on 25.05.2024.
//

#ifndef PROJECT_GAME2D_RENDERMANAGER_H
#define PROJECT_GAME2D_RENDERMANAGER_H
#include "SFML/Graphics.hpp"
#include "vector"

class renderManager {
    std::vector<sf::Drawable*> drawableObjs;
    sf::RenderWindow* window;
public:
    void addObj(sf::Drawable* obj){
        drawableObjs.push_back(obj);
    }
    renderManager(sf::RenderWindow* wdw){
        window = wdw;
    }
    void DrawAll();
};


#endif //PROJECT_GAME2D_RENDERMANAGER_H
