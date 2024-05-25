//
// Created by Jeremi on 24.05.2024.
//

#include "meleeEnemy.h"
#include "vmath.h"


void meleeEnemy::damagePlayer(float ammount) {
    if(vmath::distV(getScreenPos(),player->getScreenPos())<=radius+player->radius) {
        player->damage(ammount);
        player->moveDir(-(getScreenPos()-player->getScreenPos())*0.05f);
        knockBack((getScreenPos()-player->getScreenPos()),-.05);
    }
}