//
// Created by Jeremi on 17.05.2024.
//

#include "Staff.h"
#include "Weapon.h"
#include "vmath.h"
#include "cmath"
#include "iostream"
#include <ctime>
#include "SFML/Graphics.hpp"

// for random number https://www.boardinfinity.com/blog/rand-function-in-c/

void Staff::hit() {
    for (int i = 0; i < enemies->size(); ++i) {
        sf::Vector2f enemyPos = (*enemies)[i]->getScreenPos();
        attackGfx.setPosition(center-sf::Vector2f(range, range));

        if(vmath::distV(enemyPos,center)<=range+(*enemies)[i]->radius){
            (*enemies)[i]->knockBack(center-enemyPos,.5);

            if(critChance>=critNumber){
                (*enemies)[i]->damage(damage*critMultiplier);
                attackGfx.setFillColor(sf::Color::Red);
                player->onCrit = true;
            }
            else{
                (*enemies)[i]->damage(damage);
            }

        }
    }
    renderM->addObj(&attackGfx);
}