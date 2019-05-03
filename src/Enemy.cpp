#include "Enemy.h"



Enemy::Enemy( Texture& tex, int fType, Vector2i pos)
{
    if(fType >= 0 && fType < 3)
        type = fType;
    else
        type = 0;
    sprite = new Animation(type, tex);
    sprite->setPosition(pos.x, pos.y);
    collision_box = new RectangleShape({26,26});
    collision_box->setOrigin(collision_box->getSize().x/2, collision_box->getSize().y/2);
    collision_box->setPosition(getPosition());
    collision_box->setFillColor({255,0,0});
    collision_box->setRotation(45);
}

Enemy::~Enemy()
{
    delete sprite;
    delete collision_box;
}


void Enemy::move(Vector2f dir, float time)
{

    sprite->move(dir, time, SPEED);
    collision_box->move(dir.x * SPEED * time , dir.y * SPEED * time );

}

void Enemy::updateAnim()
{
    sprite->update();
}


Sprite Enemy::getSprite(){
    return sprite->getCurrent();
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
void Enemy::setPosition(int x, int y)
{
    sprite->setPosition(x, y);
}

