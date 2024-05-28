//
// Created by Jeremi on 25.05.2024.
//

#include "renderManager.h"

void renderManager::DrawAll() {
    for(sf::Drawable* d : drawableObjs){
        window->draw(*d);
    }
    drawableObjs.clear(); //https://stackoverflow.com/questions/12795196/clearing-a-vector-of-pointers
    drawableObjs = std::vector<sf::Drawable*>();
}