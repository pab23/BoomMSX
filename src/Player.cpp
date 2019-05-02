#include "Player.h"

Player::Player(Texture& sheet)
{

    spr = new Sprite(sheet);
    spr->setOrigin(17.5, 17.5);
    spr->setTextureRect(sf::IntRect(0, 0, 35, 35));
    resetPosition();

}

Player::~Player()
{
    delete spr;
}
void Player::move(bool dir, float time)
{
    if(dir)
        spr->move((SPEED * time * 1000), 0);
    else
        spr->move((-SPEED * time * 1000), 0);
}


Sprite Player::getSprite()
{
    return *spr;
}

Vector2f Player::getPosition()
{
    return spr->getPosition();
}

FloatRect Player::getBounds()
{
    return spr->getGlobalBounds();
}

void Player::resetPosition()
{
    spr->setPosition(390,520);
}
