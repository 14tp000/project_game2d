#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "vmath.h"
#include "./maps/Map.h"
#include "Weapon.h"
#include "Staff.h"
#include "RangedWpn.h"
#include "vector"
#include "meleeEnemy.h"
#include "rangedEnemy.h"
#include "renderManager.h"
#include "Boss.h"

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

void updateEnemies(std::vector<Enemy*>& enemies, float dt){
    for(Enemy* enemy : enemies){
        enemy->dt = dt;
        enemy->shunt(80, dt);
        enemy->Update();

        if(!enemy->dead) {
            enemy->MoveToPlayer();
            enemy->damagePlayer(10.f);
        }
    }
}


auto main() -> int {

    const unsigned int borderX = 1920;
    const unsigned int borderY = 1080;
    const unsigned int mapX = 5846;
    const unsigned int mapY = 4134;
    auto window = sf::RenderWindow(
            sf::VideoMode({borderX, borderY}), "Test",
            sf::Style::Fullscreen, sf::ContextSettings(0, 0, 8)
    );

    Map map = Map("..\\maps\\mapImages\\map1.png");
    sf::Texture mTexture;
    mTexture.loadFromImage(map.img);

    Map mapColls = Map("..\\maps\\mapImages\\map1_collisions.png");
    sf::Texture cTexture;

    renderManager rM = renderManager(&window);

    Player player = Player(0, 0,mapColls.img,100,&rM);
    cTexture.loadFromImage(mapColls.img);


    std::vector<Enemy*> enemies;

    enemies.push_back(new rangedEnemy(sf::Vector2f(500,500),50, &mapColls.img, &player,100,200,&rM, 350));
    enemies.push_back(new meleeEnemy(sf::Vector2f(1000,1000),50, &mapColls.img, &player,100, &rM, 420));

    std::vector<sf::Vector2f> pos;
    pos.push_back(sf::Vector2f(3000,1800));
    pos.push_back(sf::Vector2f(2800,2200));
    pos.push_back(sf::Vector2f(3000,2400));


    auto delay2 = wait(nullptr, &rM, 1.f);
    auto atk2 = attack2(&delay2, &rM, 10,10,300, 100, 2.f, 0.5f);
    auto delay1 = wait(&atk2, &rM, 2.f);
    auto atk1 = attack1(&delay1, &rM, 8, 20, 0.5f, 6.f);
    delay2.setNext(&atk1);

    //auto boss = new Boss(sf::Vector2f(3000,2000),80, &mapColls.img, &player,1000, &rM, 50, &pos, 1500, &atk1);

//    enemies.push_back(boss);
//    atk1.setBoss(boss);
//    atk2.setBoss(boss);
//    delay1.setBoss(boss);
//    delay2.setBoss(boss);

    enemies.push_back(new meleeEnemy(sf::Vector2f(4000,1000),50, &mapColls.img, &player,100, &rM, 420));
    enemies.push_back(new rangedEnemy(sf::Vector2f(4000,850),50, &mapColls.img, &player,100, 200,&rM, 350));
    enemies.push_back(new meleeEnemy(sf::Vector2f(4000,650),50, &mapColls.img, &player,100,&rM, 420));

    Staff wpn = Staff(20.f, 20, 2, 100.f, sf::Vector2f(borderX/2, borderY/2), 0.5f, player, enemies,&rM);

    RangedWpn rWpn = RangedWpn(10.f, 20, 1.5, 0.f, sf::Vector2f(borderX/2, borderY/2),0.2f, player, enemies,&rM);



    sf::Shader shader;
    sf::Shader slider;
    sf::Sprite canvas;
    canvas.setTexture(mTexture);
    canvas.setScale(1,1);

    float counter = 0;
    float counter2 = 0;
    if (!shader.loadFromFile("./collShader.frag", sf::Shader::Fragment)||!slider.loadFromFile("./sliderShader.frag", sf::Shader::Fragment)) {
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


            canvas.setPosition(player.getPosition());
            window.draw(canvas);



            //std::cout<<"fps: "<<1/dt.asSeconds()<<"\n";

            player.moveDir(getMoveDir(dt.asSeconds()/1.5));
            player.shunt(80, dt.asSeconds());
            rWpn.dt = dt.asSeconds();
            rWpn.fireDir = vmath::normaliseVector(sf::Vector2f(sf::Mouse::getPosition())-sf::Vector2f(borderX/2, borderY/2));
            rWpn.Update();


            updateEnemies(enemies, dt.asSeconds());


            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&& wpn.attackCd<=counter)
            {
                wpn.attackGfx.setFillColor(sf::Color::White);
                counter = 0;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& rWpn.attackCd<=counter2)
            {
                rWpn.hit();
                counter2 = 0;
            }

            shader.setParameter("collMap",cTexture);
            shader.setParameter("resolution",sf::Vector2f(mapX,mapY));
            shader.setParameter("u_position",sf::Vector2f(borderX/2, borderY/2)-player.getPosition());

            slider.setParameter("start", sf::Vector2f(100,100));
            slider.setParameter("end", sf::Vector2f(400,150));
            slider.setParameter("filled", player.getCurrentHp()/player.getMaxHP());
            slider.setParameter("fillColor",1.,0.,0.,1.);
            slider.setParameter("bgColor",1.,0.,0.,0.3);

            if(counter<0.1){
                wpn.hit();
            }
            player.update();
            rM.DrawAll();

            window.draw(sf::RectangleShape(sf::Vector2f(borderX,borderY)), &shader);
            window.draw(sf::RectangleShape(sf::Vector2f(borderX,borderY)), &slider);
            window.display();
            counter +=dt.asSeconds();
            counter2 +=dt.asSeconds();
            dt = deltaClock.restart();
        }
    }
}