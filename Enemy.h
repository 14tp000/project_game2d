//
// Created by Jeremi on 11.05.2024.
//

#ifndef PROJECT_GAME2D_ENEMY_H
#define PROJECT_GAME2D_ENEMY_H


class Enemy {
    public:
        sf::CircleShape gfx;
        sf::CircleShape debugGfx;
        sf::CircleShape debugGfx2;
        sf::Vector2f position;
        sf::Vector2f playerPos;
        float speed = 2.f;
        float radius;
        float aggroRadius = 700.f;
        sf::Image collMap; //TODO: zrobić lepiej

        void Update(sf::Vector2f playerP);
        bool inLOS(sf::Vector2f point);
        void MovePosition(sf::Vector2f pos,float spd);
        bool moveToNearLOSPoint(sf::Vector2f pos);
        void MoveToPlayer();
        bool isIn(sf::Vector2f point);
        void shunt(int rayNum, float shuntDist);
        Enemy(sf::Vector2f startPos, float rad, sf::Image collMap){
            radius = rad;
            position = startPos;
            gfx = sf::CircleShape(rad, 32);
            debugGfx = sf::CircleShape(30, 32);
            debugGfx2 = sf::CircleShape(30, 32);
            this->collMap = collMap;
        }
};


#endif //PROJECT_GAME2D_ENEMY_H
