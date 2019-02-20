#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Enemy.h"
#include "Bullet.h"

#define width 800
#define height 600
#define vel 5

std::vector<Bullet> colision(const std::vector<Bullet> &fBullets)
{
    std::vector<Bullet> devuelve = fBullets;
    std::vector<Bullet>::iterator it;
    for(it = devuelve.begin(); it != devuelve.end(); it++)
    {
        if(it->getPos().y < 0 || it->getPos().y > height)
        {
            devuelve.erase(it);
        }
    }
    return devuelve;
}

int main()
{



    //WINDOW SETTINGS
    sf::RenderWindow app(sf::VideoMode(width, height), "Boom MSX Remastered");
    app.setMouseCursorVisible(false);
    app.setFramerateLimit(60);


    //BACKGROUND SETTINGS
    sf::Texture bg;
    bg.loadFromFile("bg.png");
    sf::Sprite bgSprite;
    sf::Vector2u sizebg = bg.getSize();
    bgSprite.setTexture(bg);
    bgSprite.scale(0.390625, 0.390625);

    //PLAYER SETTINGS

    sf::Texture texSheet;
    texSheet.loadFromFile("mySheet.png");
    sf::Sprite play1(texSheet);
    play1.setOrigin(17.5, 17.5);
    play1.setTextureRect(sf::IntRect(0, 0, 35, 35));
    play1.setPosition(390,520);



    //ENEMIES SETTINGS
    sf::Sprite ex(texSheet);
    ex.setTextureRect(sf::IntRect(35,0, 32, 32));
    ex.rotate(-90);
    ex.setScale(1.25, 1.5);
    ex.setOrigin(16, 16);


    std::vector<Enemy> enemies;
    int posX  = 150, posY = 100;
    for( int i = 0; i < 12; i++){
        ex.setPosition(posX , posY);
        Enemy aux(ex, 1, 0);
        enemies.push_back(aux);
        posX += 100;
        if(posX >= 750){
            posX = 150;
            posY += 100;
        }

    }

    //BULLETS
    std::vector<Bullet> bullets;


    //SCORE SETTINGS
    unsigned int score = 0;
    std::stringstream ss;
    ss <<"SCORE: "<< score;
    sf::Font font;
    font.loadFromFile("ARCADE.TTF");
    sf::Text scoreT(ss.str().c_str(), font);
    scoreT.setCharacterSize(25);
    scoreT.setOrigin(0, 25);
    scoreT.setPosition(30, 570);


	// GAME LOOP
    while (app.isOpen())
    {
        // Process events
        std::cout<<cont<<std::endl;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            bullets.push_back(Bullet(texSheet, play1.getPosition().x, play1.getPosition().y-26));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            printf("Bullets created: %d", (int)bullets.size());
            app.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(play1.getPosition().x < width-20)
            {
                play1.move(vel, 0);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(play1.getPosition().x > 20)
            {
                play1.move(-vel, 0);
            }
        }
        cont --;
        for(unsigned z = 0; z < bullets.size(); z++ )
        {
            bullets[z].move();
        }
        bullets = colision(bullets);
        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(bgSprite);
        app.draw(play1);
        for(unsigned z = 0; z < bullets.size(); z++)
        {
            app.draw(bullets[z].getSprite());
        }


        for(unsigned j = 0; j < enemies.size(); j++)
            app.draw(enemies[j].getSprite());
        app.draw(scoreT);

        // Update the window
        app.display();
    }

    return 0;
}
