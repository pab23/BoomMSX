#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "SFML/Graphics.hpp"

#define MAX_VIDA 50
#define SPEED 5

using namespace std;
using namespace sf;

class Player
{
    public:
        Player(Texture&);
        virtual ~Player();

        void move(bool, float);

        void setVida(int);
        Sprite getSprite();
        Vector2f getPosition();
        FloatRect getBounds();
        int getHp();

    private:
        Sprite* spr;
        int hp;
};

#endif // PLAYER_H
