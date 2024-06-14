//
// Created by Jeremi on 24.05.2024.
//

#include "Destructible.h"


void Destructible::damage(float ammount) {
    if(!dead) {
        currentHP -= ammount;
        if (currentHP < 0) {
            currentHP = 0;
            die();
        }
    }
}