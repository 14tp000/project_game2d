//
// Created by Jeremi on 14.06.2024.
//

#ifndef PROJECT_GAME2D_CANVAS_H
#define PROJECT_GAME2D_CANVAS_H
#include "SFML/Graphics.hpp"
#include "vector"
#include "map"
#include "algorithm"
#include "renderManager.h"
#include "iostream"

class Canvas {
public:
    std::vector<std::pair<int, sf::Drawable*>> objects;
    renderManager* rM;

    Canvas(renderManager* renderManager){
        rM = renderManager;
    }

    void addObj(sf::Drawable* object, int layer){
        objects.push_back({layer, object});
        Sort();
    }
    void addObj(sf::Drawable* object){
        objects.push_back({0, object});
        Sort();
    }

    void Sort(){
        std::ranges::sort(objects,{},[](auto obj) {return obj.first;});
    }

    void Draw(){
        for(auto obj: objects){
            rM->addGUI(obj.second);
        }
    }
};


#endif //PROJECT_GAME2D_CANVAS_H
