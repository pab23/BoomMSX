#include "Enemy.h"



Enemy::Enemy( sf::Sprite fSprite, int fHp, int fType)
{
    if(fHp > 0)
        hp = fHp;
    else
        hp = 1;
    if(fType >= 0 && fType < 3)
        type = fType;
    else
        type = 0;
    sprite = new sf::Sprite(fSprite);
}

Enemy::~Enemy()
{
    delete sprite;
    hp = type = 0;
}


void Enemy::move(Vector2f dir, float time)
{
    sprite->move(dir.x * SPEED * time * 1000, dir.y * SPEED * time * 1000);
}



sf::Sprite Enemy::getSprite(){
    return *sprite;
}

Vector2f Enemy::getPosition()
{
    return sprite->getPosition();
}
FloatRect Enemy::getBounds()
{
    return sprite->getGlobalBounds();
}
