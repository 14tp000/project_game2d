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

void MovementOnCrit::Update() {
    if(enabled) {
        if (active) {
            gfx.setFillColor(sf::Color::Red);
        } else {
            gfx.setFillColor(sf::Color(100, 100, 100));
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
}