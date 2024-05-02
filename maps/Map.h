//
// Created by Jeremi on 25.04.2024.
//

#ifndef PROJECT_GAME2D_MAP_H
#define PROJECT_GAME2D_MAP_H


class Map {
public:
    sf::Image img;
    Map(sf::Image img){
        this->img =img;
    }
    Map(std::string path){
        img.loadFromFile(path);
    }
    //bool isIn(sf::Vector2f point);
    sf::Texture getTexture();
};


#endif //PROJECT_GAME2D_MAP_H
