//
// Created by Jeremi on 13.06.2024.
//

#include "WeaponManager.h"

void WeaponManager::Attack(int i) {
    weapons[i]->hit();
}

void WeaponManager::UpdateWeapons() {
    for(auto wpn:weapons){
        wpn->Update(dt);
    }
}

void WeaponManager::SetCritNumbers(int cn) {
    for(auto wpn:weapons){
        wpn->critNumber = cn;
    }
}