#include "Bullet.h"

#define bulletSpeed 0.25

Bullet::Bullet()
{
    //ctor
}

Bullet::Bullet(sf::Texture &texture, float pos_x, float pos_y)
{
    sprite = sf::Sprite(texture);
    sprite.setOrigin(10, 10);
    sprite.setTextureRect(sf::IntRect(35+(32*4), 0, 20, 20));
    sprite.setPosition(pos_x, pos_y);
}

void Bullet::move()
{
    sprite.move(0, -bulletSpeed);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}

sf::Vector2f Bullet::getPos()
{
    return sprite.getPosition();
}

sf::FloatRect Bullet::getBounds()
{
    return sprite.getGlobalBounds();
}
