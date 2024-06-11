//
// Created by Jeremi on 11.06.2024.
//

#include "Collectible.h"

void Collectible::Update() {
    if(!collected){
//        std::cout<<vmath::distV(player->getScreenPos(), position+sf::Vector2f(25,25) + player->getPosition())<<"    "<<collectRadius+player->radius<<"\n";
        if(vmath::distV(player->getScreenPos(), position+sf::Vector2f(25,25) + player->getPosition())<=collectRadius+player->radius){
            Trigger();
            collected = true;
        }
        gfx.setPosition(position+sf::Vector2f(25,25) + player->getPosition());
        player->renderM->addObj(&gfx);
    }
}

void HealCollectible::Trigger() {
    player->heal(healAmmount);
}