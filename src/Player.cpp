#include "Player.h"

Player::Player(Texture& sheet)
{
    hp = MAX_VIDA;

    spr = new Sprite(sheet);
    spr->setOrigin(17.5, 17.5);
    spr->setTextureRect(sf::IntRect(0, 0, 35, 35));
    spr->setPosition(390,520);

}

Player::~Player()
{
    delete spr;
    hp = 0;
}
void Player::move(bool dir, float time)
{
    if(dir)
        spr->move((SPEED * time * 1000), 0);
    else
        spr->move((-SPEED * time * 1000), 0);
}

void Player::setVida(int vi)
{
    if(hp + vi < MAX_VIDA && hp + vi > 0)
        hp += vi;
    else if(hp + vi <= 0)
        hp = 0;
    else
        hp = MAX_VIDA;

    cout << "HP: " << hp << endl;
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

int Player::getHp()
{
    return hp;
}
