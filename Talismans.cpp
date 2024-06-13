//
// Created by Jeremi on 10.06.2024.
//

#include "Talismans.h"
#include "iostream"

void MovementOnCrit::Trigger() {
    if (!active) {
        counter = 0;
        player->movementSpeed *= speedMultiplier;
        active = true;
    }
}

void CConMeleeHit::Trigger() {
    if(!active){
        counter = 0;
        for(auto wpn: WM->weapons){
            wpn->critChance+=ccBoost;
        }
        active = true;
    }
}

void CConMeleeHit::Update() {
    if(enabled) {
        if (active) {
            gfx.setFillColor(sf::Color::Green);
        } else {
            gfx.setFillColor(sf::Color(150, 150, 150));
        }

        player->renderM->addGUI(&gfx);

        if (player->onMeleeHit) {
            Trigger();
        }
        if (active) {
            counter += dt;
            if (counter >= duration) {
                for(auto wpn: WM->weapons){
                    wpn->critChance-=ccBoost;
                }
                active = false;
            }
        }
    }
    else{
        gfx.setFillColor(sf::Color(50, 50, 50));
    }
}


void MovementOnCrit::Update() {
    if(enabled) {
        if (active) {
            gfx.setFillColor(sf::Color::Red);
        } else {
            gfx.setFillColor(sf::Color(150, 150, 150));
        }

        player->renderM->addGUI(&gfx);
        if (player->onCrit) {
            Trigger();
        }
        if (active) {
            counter += dt;
            if (counter >= duration) {
                player->movementSpeed /= speedMultiplier;
                active = false;
            }
        }
    }
    else{
        gfx.setFillColor(sf::Color(50, 50, 50));
    }
}