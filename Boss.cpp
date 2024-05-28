//
// Created by Jeremi on 28.05.2024.
//

#include "Boss.h"
#include "iostream"
#include "vmath.h"
#include "random" //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range

void Boss::MoveToPlayer() {
    if(10>vmath::distV(getGlobalPos(), (*patrolPts)[i])){
        i++;
        if(i>=patrolPts->size()){
            i = 0;
        }
    }
    MoveGlobalPosition((*patrolPts)[i],speed);
}

void attack1::Render() {
    for(int i = 0;i<1;i++) {
        auto circle = new sf::CircleShape(20,32);
        circle->setPosition(sf::Vector2(0.f,0.f));
        rM->addObj(circle);
    }
}

void attack2::Render() {
    for(int i = 0;i<1;i++) {
        auto circle = new sf::CircleShape(20,32);
        circle->setPosition(sf::Vector2(10.f,10.f));
        rM->addObj(circle);
    }
}



void attack1::attackPlayer() {
    std::cout << "attack1";
    boss->gfx.setFillColor(sf::Color::Blue);
    Render();
    counter+=boss->dt;
    if(counter>duration){
        finished = true;
    }
}
void attack2::attackPlayer() {
    std::cout<<"attack2";
    boss->gfx.setFillColor(sf::Color::Red);
    Render();
    counter+=boss->dt;
    if(counter>duration){
        finished = true;
    }
}


void Boss::damagePlayer(float ammount) {

    if(vmath::distV(player->getScreenPos(), getScreenPos())<attackDist&& inLOS(player->getScreenPos(), getScreenPos())){
//        gfx.setFillColor(sf::Color::Cyan);
        if(!attack->finished) {
            attack->attackPlayer();
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