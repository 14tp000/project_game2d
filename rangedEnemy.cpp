//
// Created by Jeremi on 25.05.2024.
//

#include "rangedEnemy.h"
#include "Enemy.h"
#include "vmath.h"

void rangedEnemy::MoveToPlayer() {
    float dist = vmath::distV(player->getScreenPos(),getScreenPos());
    if(dist>stopDist){
        Enemy::MoveToPlayer();
    }
}
void rangedEnemy::damagePlayer(float ammount) {
    if(counter>=attackDelay&&inPlayerLOS) {

        if(projectileI>=bullets.size()) {
//            bullets.push_back(std::make_unique<Projectile>(
//                    Projectile(800, -vmath::normaliseVector(getScreenPos()-player->getScreenPos()), 20, getGlobalPos(), player->getPosition())));

            bullets.push_back(new Projectile(800, -vmath::normaliseVector(getScreenPos()-player->getScreenPos()), 20, getGlobalPos(), player->getPosition()));

        }
        else{
            delete(bullets[projectileI]); //// I really don't know why game crashed when i tried to overwrite smart pointers... anyway, it works this way
//            bullets[projectileI] = std::make_unique<Projectile>(
//                    Projectile(1, sf::Vector2f(1,0), 20, getGlobalPos(), player->getPosition()));
            bullets[projectileI] = new Projectile(800, -vmath::normaliseVector(getScreenPos()-player->getScreenPos()), 20, getGlobalPos(), player->getPosition());
        }
        projectileI++;
        if(projectileI>=maxNumProjectiles){
            projectileI = 0;
        }
        counter = 0;
    }
}

void rangedEnemy::Update() {
    for(int i = 0;i<bullets.size();i++){
        if(player->isIn(bullets[i]->getGlobalPos())){ bullets[i]->isKilled = true; }
        if(!bullets[i]->isKilled) {
            bullets[i]->playerPos = player->getPosition();
            bullets[i]->position += bullets[i]->speed * bullets[i]->direction*dt;
            bullets[i]->Update();
            renderM->addObj(&(bullets[i]->gfx));
            float dst = vmath::distV(bullets[i]->getScreenPos(), player->getScreenPos());
            if ( dst<=
                player->radius + bullets[i]->radius) {
                player->moveDir(bullets[i]->direction*(20.f));
                player->damage(10);
                bullets[i]->isKilled = true;
            }

        }
    }
    Enemy::Update();
    counter +=dt;
}