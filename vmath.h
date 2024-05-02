//
// Created by Jeremi on 25.04.2024.
//

#ifndef PROJECT_GAME2D_VMATH_H
#define PROJECT_GAME2D_VMATH_H


class vmath {
public:
    static sf::Vector2f rotateVector(sf::Vector2f v, float angle);
    static float vectorMagnitude(sf::Vector2f v);
    static sf::Vector2f normaliseVector(sf::Vector2f v);
};


#endif //PROJECT_GAME2D_VMATH_H
