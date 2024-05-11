#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "vmath.h"
#include "./maps/Map.h"

//https://www.sfml-dev.org/tutorials/2.0/graphics-shader.php, and https://thebookofshaders.com/edit.php used for help with adding shaders


sf::Vector2f getMoveDir(float dt){
    sf::Vector2f dir = sf::Vector2f(0, 0);
    float speed = 700;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dir+=sf::Vector2f(-1,0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dir+=sf::Vector2f(1,0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dir+=sf::Vector2f(0,-1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dir+=sf::Vector2f(0,1);
    }


    dir = vmath::normaliseVector(dir)*speed*dt;
    return dir;
}

auto main() -> int {
    unsigned int borderX = 1920;// softcode this
    unsigned int borderY = 1080;
    auto window = sf::RenderWindow(
            sf::VideoMode({borderX, borderY}), "Test",
            sf::Style::Fullscreen, sf::ContextSettings(0, 0, 8)
    );

    Map map = Map("D:\\Users\\Jeremi\\CLionProjects\\project_game2d\\maps\\mapImages\\map1.png");
    sf::Texture mTexture;
    mTexture.loadFromImage(map.img);

    Map mapColls = Map("D:\\Users\\Jeremi\\CLionProjects\\project_game2d\\maps\\mapImages\\map1_collisions.png");
    sf::Texture cTexture;
    Player player = Player(0, 0,mapColls.img);
    cTexture.loadFromImage(mapColls.img);
    player.update();

    Enemy enemy = Enemy(sf::Vector2f(500,500),50);

    sf::Shader shader;
    sf::Sprite canvas;
    canvas.setTexture(mTexture);
    canvas.setScale(1,1);
    if (!shader.loadFromFile("./collShader.frag", sf::Shader::Fragment)) {
        std::cout<<"AMOGUUUUUUUUUUUUUUUS";
    }
    else {
        sf::Clock deltaClock;
        sf::Time dt = deltaClock.restart();//https://en.sfml-dev.org/forums/index.php?topic=7068.0
        while (window.isOpen()) {
            auto event = sf::Event();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }

            window.clear(sf::Color::Black);


            //canvas.setPosition(sf::Vector2f(borderX-player.getPosition().x,borderY-player.getPosition().y));
            canvas.setPosition(player.getPosition());
            window.draw(canvas);



            //std::cout<<"fps: "<<1/dt.asSeconds();

            player.moveDir(getMoveDir(dt.asSeconds()));
            player.shunt(80, dt.asSeconds());

            enemy.Update(player.getPosition());
            enemy.MoveToPlayer();


            shader.setParameter("collMap",cTexture);
            shader.setParameter("resolution",sf::Vector2f(5846,4134)); // texture size is 5846x4134, TODO: softcode this
            shader.setParameter("u_position",sf::Vector2f(1920/2, 1080/2)-player.getPosition());
            window.draw(sf::RectangleShape(sf::Vector2f(borderX,borderY)), &shader);

            window.draw(player.getShape());
            window.draw(enemy.gfx);


            window.display();
            dt = deltaClock.restart();
        }
    }
}