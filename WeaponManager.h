//
// Created by Jeremi on 13.06.2024.
//

#ifndef PROJECT_GAME2D_WEAPONMANAGER_H
#define PROJECT_GAME2D_WEAPONMANAGER_H
#include "Weapon.h"
#include "vector"

class WeaponManager {
public:
    float dt;
    std::vector<Weapon*> weapons;
    void addWeapon(Weapon* wpn){
        weapons.push_back(wpn);
    }
    void setDt(float deltaTime){
        dt = deltaTime;
    }
    void Attack(int i);
    void UpdateWeapons();
    void SetCritNumbers(int cn);
};


#endif //PROJECT_GAME2D_WEAPONMANAGER_H
