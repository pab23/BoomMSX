#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>


class Enemy
{
    public:
        Enemy(){hp = 1; type = 0;};
        Enemy(sf::Sprite, int, int);
        void hit();
        sf::Sprite getSprite();
        virtual ~Enemy();
    protected:
    private:
        sf::Sprite *sprite;
        unsigned int hp;
        unsigned int type;

};

#endif // ENEMY_H
