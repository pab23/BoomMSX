#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>


class Enemy
{
    public:
        Enemy(){hp = 1; type = 0;sf::Vector2f pos(0,0);};
        Enemy(sf::Vector2f, int, int);
        void hit();
        virtual ~Enemy();
    protected:
    private:
        sf::Vector2f pos;
        sf::Sprite sprite;
        unsigned int hp;
        unsigned int type;

};

#endif // ENEMY_H
