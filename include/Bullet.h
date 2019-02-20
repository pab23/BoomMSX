#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
    public:
        Bullet();
        Bullet(sf::Texture&, float, float);
        virtual ~Bullet();

        void move();
        sf::Sprite getSprite();
        sf::Vector2f getPos();

    protected:

    private:
        sf::Sprite sprite;
};

#endif // BULLET_H
