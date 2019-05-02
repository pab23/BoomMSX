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

        Sprite getSprite();
        Vector2f getPosition();
        FloatRect getBounds();

        void resetPosition();


    private:
        Sprite* spr;
};

#endif // PLAYER_H
