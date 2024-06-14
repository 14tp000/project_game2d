//
// Created by Jeremi on 17.05.2024.
//

#ifndef PROJECT_GAME2D_RANGEDWPN_H
#define PROJECT_GAME2D_RANGEDWPN_H

#include "Weapon.h"
#include "Projectile.h"
#include "vector"
#include "memory"

class RangedWpn:  public Weapon{
    int projectileI = 0;
    int maxNumProjectiles = 100;
public:
    std::vector<std::unique_ptr<Projectile>> bullets;
    sf::Vector2f fireDir;
    int critNumber;
    void hit() override;
    void Update(float dt) override;
    using Weapon::Weapon;
};


#endif //PROJECT_GAME2D_RANGEDWPN_H
