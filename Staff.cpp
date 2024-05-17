//
// Created by Jeremi on 17.05.2024.
//

#include "Staff.h"
#include "Weapon.h"
#include "vmath.h"
#include "cmath"
#include "iostream"

void Staff::hit() {
    for (int i = 0; i < enemies.size(); ++i) {
        sf::Vector2f enemyPos = enemies[i]->getScreenPos();
        attackGfx.setPosition(center-sf::Vector2f(range, range));

        if(vmath::distV(enemyPos,center)<=range+enemies[i]->radius){
            enemies[i]->knockBack(center-enemyPos,.5);
            std::cout<<"hit!";
        }
    }
}