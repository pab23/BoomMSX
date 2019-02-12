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

    sprite = fSprite;
}

Enemy::~Enemy()
{
    //dtor
}

sf::Sprite Enemy::getSprite(){
    return sprite;
}
