#include "Enemy.h"



Enemy::Enemy( sf::Sprite fSprite, int fType)
{
    if(fType >= 0 && fType < 3)
        type = fType;
    else
        type = 0;
    sprite = new Sprite(fSprite);
    collision_box = new RectangleShape({28,28});
    collision_box->setOrigin(14, 14);
    collision_box->setPosition(getPosition());
    collision_box->setFillColor({255,0,0});
}

Enemy::~Enemy()
{
    delete sprite;
    delete collision_box;
}


void Enemy::move(Vector2f dir, float time)
{
    sprite->move(dir.x * SPEED * time * 1000, dir.y * SPEED * time * 1000);
    collision_box->move(dir.x * SPEED * time * 1000, dir.y * SPEED * time * 1000);

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
    return collision_box->getGlobalBounds();
}

int Enemy::getType()
{
    return type;
}
RectangleShape Enemy::getColBox()
{
    return *collision_box;
}


