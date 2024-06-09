//
// Created by Jeremi on 28.05.2024.
//

#include "Boss.h"
#include "iostream"
#include "vmath.h"
#include "Enemy.h"


void Boss::MoveToPlayer() {
    if(10>vmath::distV(getGlobalPos(), (*patrolPts)[i])){
        i++;
        if(i>=patrolPts->size()){
            i = 0;
        }
    }
    MoveGlobalPosition((*patrolPts)[i],speed);
}

void Boss::damagePlayer(float ammount) {

    if(vmath::distV(player->getScreenPos(), getScreenPos())<attackDist&& inLOS(player->getScreenPos(), getScreenPos())){
        if(!attack->finished) {
            attack->attackPlayer();
            for (auto &bullet: bullets) {
                if (!bullet->isKilled) {
                    bullet->playerPos = player->getPosition();
                    bullet->Update();
                    bullet->position += bullet->speed * bullet->direction * dt;
                    renderM->addObj(&bullet->gfx);
                    float dst = vmath::distV(bullet->getScreenPos(), player->getScreenPos());
                    if (dst <=
                        player->radius + bullet->radius && bullet->canDamage) {
                        player->moveDir(bullet->direction * (20.f));
                        player->damage(10);
                        bullet->isKilled = true;
                    }
                    if (isIn(bullet->getGlobalPos())) { bullet->isKilled = true; }
                }
            }

        }
        else {
            attack = attack->getNext();
            attack->Reset();
        }
    }
    else{
        gfx.setFillColor(sf::Color::Magenta);
    }
}

void attack1::attackPlayer() {
    Render();
    if(delay<ctr) {
        for (int i = 0; i < numBullets; i++) {

            sf::Vector2f dir = sf::Vector2f(1, 0);
            if(boss->projectileI>=boss->bullets.size()){
                boss->bullets.push_back(std::make_unique<Projectile>(200, vmath::rotateVector(dir, M_PI * 2 / numBullets * i+angleOffset), radius,
                                                                                       boss->position + sf::Vector2f(boss->radius, boss->radius),
                                                                                       boss->player->getPosition()));
            }
            else{
                boss->bullets[boss->projectileI] = std::make_unique<Projectile>(200, vmath::rotateVector(dir, M_PI * 2 / numBullets * i+angleOffset), radius,
                                                                                boss->position + sf::Vector2f(boss->radius, boss->radius),
                                                                                boss->player->getPosition());
            }

            boss->projectileI++;
            if(boss->projectileI>=boss->maxNumProjectile){
                boss->projectileI = 0;
            }

        }
        ctr = 0;
        angleOffset+=angleOffsetStep;
    }

    counter+=boss->dt;
    ctr+=boss->dt;
    if(counter>duration){
        finished = true;
    }
}

void attack2::attackPlayer() {
    Render();

    if(counter == 0){

        for (auto& bullet: boss->bullets) {
            bullet->isKilled = true;
        }


        for (int x = 0; x < numBulletsX; x++) {
            for(int y = 0;y<numBulletsY;y++) {

                if(boss->projectileI>=boss->bullets.size()){
                    boss->bullets.push_back(std::make_unique<Projectile>(0, sf::Vector2f(0, 0), radius,
                                                                                boss->position + sf::Vector2f(x*step-numBulletsX*step/2,y*step-numBulletsY*step/2)
                                                                                + sf::Vector2f(boss->radius, boss->radius),
                                                                                boss->player->getPosition()));
                    boss->bullets[boss->projectileI]->gfx.setFillColor(sf::Color::Red);
                    boss->bullets[boss->projectileI]->canDamage = false;
                }
                else{
                    boss->bullets[boss->projectileI] = std::make_unique<Projectile>(0, sf::Vector2f(0, 0), radius,
                                                                                    boss->position + sf::Vector2f(x*step-numBulletsX*step/2,y*step-numBulletsY*step/2)
                                                                                    + sf::Vector2f(boss->radius, boss->radius),
                                                                                    boss->player->getPosition());
                    boss->bullets[boss->projectileI]->gfx.setFillColor(sf::Color::Red);
                    boss->bullets[boss->projectileI]->canDamage = false;
                }

                boss->projectileI++;
                if(boss->projectileI>=boss->maxNumProjectile){
                    boss->projectileI = 0;
                }
            }
        }
    }
    else if(counter >= activate*duration){
        for(auto& bullet : boss-> bullets) {
            bullet->gfx.setFillColor(sf::Color::White);
            bullet->canDamage = true;
        }
    }
    else if(counter <duration*activate){
        for(auto& bullet : boss-> bullets) {
            bullet->gfx.setRadius(counter/(duration*activate)*radius);
        }
    }

    counter+=boss->dt;
    if(counter>duration){

        for (auto& bullet: boss->bullets) {
            bullet->isKilled = true;
        }

        finished = true;
    }
}

void wait::attackPlayer() {
    Render();
    counter+=boss->dt;

    if(counter>duration){
        finished = true;
    }
}


void attack1::Render() {boss->gfx.setFillColor(sf::Color::Green);}
void attack2::Render() {boss->gfx.setFillColor(sf::Color::Yellow);}
void wait::Render() {boss->gfx.setFillColor(sf::Color::Blue);}
