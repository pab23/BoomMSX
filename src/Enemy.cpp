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


void Enemy::move(Vector2i dir)
{
    sprite->move(dir.x*speed, dir.y*speed);
}



sf::Sprite Enemy::getSprite(){
    return *sprite;
}

Vector2f Enemy::getPosition()
{
    return sprite->getPosition();
}
