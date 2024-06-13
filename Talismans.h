//
// Created by Jeremi on 10.06.2024.
//

#ifndef PROJECT_GAME2D_TALISMANS_H
#define PROJECT_GAME2D_TALISMANS_H

#include "Player.h"
#include "Weapon.h"
#include "vector"
#include "WeaponManager.h"


class MovementOnCrit: public Talisman{
public:
    float speedMultiplier;
    WeaponManager* WM;
    void Update() override;
    void Trigger() override;
    MovementOnCrit(Player* plr, float dur, float spdM, sf::Vector2f gfxPos): Talisman(plr, dur, gfxPos){speedMultiplier = spdM;}
};

class CConMeleeHit: public Talisman{
public:
    int ccBoost;
    WeaponManager* WM;
    void Update() override;
    void Trigger() override;
    CConMeleeHit(Player* plr, float dur, int ccB, sf::Vector2f gfxPos): Talisman(plr, dur, gfxPos){ccBoost = ccB;}
};



#endif //PROJECT_GAME2D_TALISMANS_H
