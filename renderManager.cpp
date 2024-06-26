//
// Created by Jeremi on 25.05.2024.
//

#include "renderManager.h"

void renderManager::DrawAll() {
    for(sf::Drawable* d : drawableObjs){
        window->draw(*d);
    }
    drawableObjs.clear();
}

void renderManager::DrawGUI() {
    for(sf::Drawable* d : drawableGUI){
        window->draw(*d);
    }
    drawableGUI.clear();
}