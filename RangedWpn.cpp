//
// Created by Jeremi on 17.05.2024.
//

#include "RangedWpn.h"
#include "Weapon.h"
#include "vmath.h"
#include "cmath"
#include "iostream"
#include <vector>


void RangedWpn::hit() {
    bullets.push_back(new Projectile(700, fireDir,20, center-player->getPosition(), player->getPosition()));
}

void RangedWpn::Update() {
    for(int i = 0;i<bullets.size();i++){
        if(player->isIn(bullets[i]->getGlobalPos())){ bullets[i]->isKilled = true; }
        if(!bullets[i]->isKilled) {
            bullets[i]->playerPos = player->getPosition();
            bullets[i]->position += bullets[i]->speed * bullets[i]->direction*dt;
            bullets[i]->Update();
            renderM->addObj(&(bullets[i]->gfx));
            for (int j = 0; j < enemies->size(); j++) {
                //std::cout<<"erad: "<<enemies[j]->radius<<" brad: "<<bullets[i]->radius<<" dist = "<<vmath::distV(bullets[i]->getGlobalPos(), enemies[j]->getGlobalPos())<<"\n";
                if (vmath::distV(bullets[i]->getGlobalPos(), (*enemies)[j]->getGlobalPos()) <=
                    (*enemies)[j]->radius + bullets[i]->radius) {
                    (*enemies)[j]->knockBack(bullets[i]->direction, -50);
                    (*enemies)[j]->damage(10);
                    bullets[i]->isKilled = true;
                }
            }
        }
    }
}