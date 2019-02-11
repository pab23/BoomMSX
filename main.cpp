#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Enemy.h"

#define width 800
#define height 600
#define vel 10


int main()
{



    //WINDOW SETTINGS
    sf::RenderWindow app(sf::VideoMode(width, height), "Boom MSX Remastered");
    app.setMouseCursorVisible(false);


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



    //PRUEBA DE ENEMIGOS
    sf::Sprite ex(texSheet);
    ex.setTextureRect(sf::IntRect(35,0, 32, 32));
    ex.rotate(-90);
    ex.setScale(1.25, 1.5);
    ex.setOrigin(16, 16);
    ex.setPosition(390,100);

    sf::Sprite bullet(texSheet);
    bullet.setOrigin(10, 10);
    bullet.setTextureRect(sf::IntRect(35+(32*4), 0, 20, 20));
    //ENEMIES SETTINGS
    std::vector<Enemy> enemies;

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
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            switch(event.type)
            {
             case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Q:
                        app.close();
                        break;
                    case sf::Keyboard::Right:
                        if(play1.getPosition().x < width-20)
                        {
                            play1.move(vel, 0);
                        }
                        break;
                    case sf::Keyboard::Left:
                        if(play1.getPosition().x > 20)
                        {
                            play1.move(-vel, 0);
                        }
                        break;
                    case sf::Keyboard::Space:
                        bullet.setPosition(play1.getPosition().x, play1.getPosition().y-26);

                    default:
                    break;
                }
                break;

            default:
                break;

            }
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(bgSprite);
        app.draw(play1);
        app.draw(bullet);
        app.draw(ex);
        app.draw(scoreT);

        // Update the window
        app.display();
    }

    return 0;
}
