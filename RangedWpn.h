//
// Created by Jeremi on 17.05.2024.
//

#ifndef PROJECT_GAME2D_RANGEDWPN_H
#define PROJECT_GAME2D_RANGEDWPN_H

#include "Weapon.h"
#include "Projectile.h"
#include "vector"

class RangedWpn:  public Weapon{
public:
    std::vector<Projectile*> bullets;
    sf::Vector2f fireDir;
    void hit();
    void Update();
    using Weapon::Weapon;
};


#endif //PROJECT_GAME2D_RANGEDWPN_H