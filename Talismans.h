//
// Created by Jeremi on 10.06.2024.
//

#ifndef PROJECT_GAME2D_TALISMANS_H
#define PROJECT_GAME2D_TALISMANS_H

#include "Player.h"


class MovementOnCrit: public Talisman{
public:
    float speedMultiplier;
    void Update() override;
    void Trigger() override;
    MovementOnCrit(Player* plr, float dur, float spdM, sf::Vector2f gfxPos): Talisman(plr, dur, gfxPos){speedMultiplier = spdM;}
};



#endif //PROJECT_GAME2D_TALISMANS_H
