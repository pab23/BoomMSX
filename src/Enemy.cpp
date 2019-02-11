#include "Enemy.h"


Enemy::Enemy(sf::Vector2f fPos, int fHp, int fType)
{
    if(fHp > 0)
        hp = fHp;
    else
        hp = 1;
    if(fType >= 0 && fType < 3)
        type = fType;
    else
        type = 0;

    pos = fPos;
}
Enemy::~Enemy()
{
    //dtor
}
