#include "Bullet.h"

#define bulletSpeed 6


Bullet::Bullet(Texture &texture, Vector2f pos, int dano, int type)
{
    sprite = new Sprite(texture);
    sprite->setOrigin(10, 10);
    sprite->setTextureRect(sf::IntRect(35+(32*4), 0, 20, 20));
    sprite->setPosition(pos);
    dmg = dano;

    if(type != 0)
        rotate();
}

Bullet::~Bullet()
{
    delete sprite;
    dmg = 0;
}
void Bullet::move(bool dir)
{
    if(dir)
        sprite->move(0, bulletSpeed);
    else
        sprite->move(0, -bulletSpeed);
}

void Bullet::rotate()
{
    sprite->rotate(180);
}

Sprite Bullet::getSprite()
{
    return *sprite;
}

Vector2f Bullet::getPos()
{
    return sprite->getPosition();
}

FloatRect Bullet::getBounds()
{
    return sprite->getGlobalBounds();
}

int Bullet::getDmg()
{
    return dmg;
}

