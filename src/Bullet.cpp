#include "Bullet.h"




Bullet::Bullet(Texture &texture, Vector2f pos, int dano, int type)
{
    sprite = new Sprite(texture);
    sprite->setOrigin(10, 10);
    sprite->setTextureRect(sf::IntRect(35+(32*4), 0, 20, 20));
    sprite->setPosition(pos);

    collision_box = new CircleShape(6);
    collision_box->setOrigin(6,6);
    collision_box->setPosition(getPos());
    collision_box->setFillColor({0,255,0});
    dmg = dano;

    if(type != 0)
        rotate();
}

Bullet::~Bullet()
{
    delete sprite;
    dmg = 0;
}
void Bullet::move(bool dir, float time)
{
    if(dir)
    {
        sprite->move(0, BULLET_SPEED * time);
        collision_box->move(0, BULLET_SPEED * time );
    }
    else
    {
        sprite->move(0, -(BULLET_SPEED * time ));
        collision_box->move(0, -(BULLET_SPEED * time ));

    }

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
    return collision_box->getGlobalBounds();
}

int Bullet::getDmg()
{
    return dmg;
}
CircleShape Bullet::getColBox()
{
    return *collision_box;
}

