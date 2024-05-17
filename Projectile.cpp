//
// Created by Jeremi on 17.05.2024.
//

#include "Projectile.h"

void Projectile::Update() {
    gfx.setPosition(getScreenPos());
}
sf::Vector2f Projectile::getScreenPos() {
    return position-sf::Vector2f(radius, radius)+playerPos;
}
sf::Vector2f Projectile::getGlobalPos() {
    return position-sf::Vector2f(radius, radius);
}