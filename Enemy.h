//
// Created by Jeremi on 11.05.2024.
//

#ifndef PROJECT_GAME2D_ENEMY_H
#define PROJECT_GAME2D_ENEMY_H


class Enemy {
    public:
        sf::CircleShape gfx;
        sf::Vector2f position;
        sf::Vector2f playerPos;
        float speed = 2.f;
        float radius;
        float aggroRadius = 500.f;
        sf::Image collMap; //TODO: zrobić lepiej

        void Update(sf::Vector2f playerP);
        bool inLOS();
        void MoveToPlayer();
        bool isIn(sf::Vector2f point);
        Enemy(sf::Vector2f startPos, float rad, sf::Image collMap){
            radius = rad;
            position = startPos;
            gfx = sf::CircleShape(rad, 32);
            this->collMap = collMap;
        }
};


#endif //PROJECT_GAME2D_ENEMY_H
