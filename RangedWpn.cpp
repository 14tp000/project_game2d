//
// Created by Jeremi on 17.05.2024.
//

#include "RangedWpn.h"
#include "vmath.h"
#include "cmath"
#include "iostream"


void RangedWpn::hit() {
    if(counter>=attackCd) {
        if(projectileI>=bullets.size()) {
            bullets.push_back(std::make_unique<Projectile>(
                    Projectile(700, fireDir, 20, center - player->getPosition(), player->getPosition())));

        }
        else{
            bullets[projectileI] = std::make_unique<Projectile>(
                    Projectile(700, fireDir, 20, center - player->getPosition(), player->getPosition()));
        }
        projectileI++;
        if(projectileI>=maxNumProjectiles){
            projectileI = 0;
        }
        counter = 0;
    }
}

void RangedWpn::Update(float dt) {
    counter+=dt;
    for(int i = 0;i<bullets.size();i++){
        if(player->isIn(bullets[i]->getGlobalPos())){ bullets[i]->isKilled = true; }
        if(!bullets[i]->isKilled) {
            bullets[i]->playerPos = player->getPosition();
            bullets[i]->position += bullets[i]->speed * bullets[i]->direction*dt;
            bullets[i]->Update();
            renderM->addObj(&(bullets[i]->gfx));
            for (int j = 0; j < enemies->size(); j++) {
                if (vmath::distV(bullets[i]->getGlobalPos(), (*enemies)[j]->getGlobalPos()) <=
                    (*enemies)[j]->radius + bullets[i]->radius) {
                    (*enemies)[j]->knockBack(bullets[i]->direction, -50);
                    if(critChance>=critNumber){
                        (*enemies)[j]->damage(damage*critMultiplier);
                        if(!player->onCrit) {
                            player->onCrit = true;
                        }
                    }
                    else{
                        (*enemies)[j]->damage(damage);
                    }
                    bullets[i]->isKilled = true;
                }
            }
        }
    }
}