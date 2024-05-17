//
// Created by Jeremi on 17.05.2024.
//

#ifndef PROJECT_GAME2D_STAFF_H
#define PROJECT_GAME2D_STAFF_H


#include "Weapon.h"

class Staff: public Weapon{
public:
    void hit();
    using Weapon::Weapon; // https://stackoverflow.com/questions/347358/inheriting-constructors
};


#endif //PROJECT_GAME2D_STAFF_H
