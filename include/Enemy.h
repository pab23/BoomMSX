#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include "Animation.h"


#define SPEED 500

using namespace sf;

class Enemy
{
    public:
        Enemy(){ type = 0;};
        Enemy(Texture&, int, Vector2i);
        virtual ~Enemy();

        void hit();
        void move(Vector2f, float);
        void updateAnim();


        Sprite getSprite();
        Vector2f getPosition();
        FloatRect getBounds();
        int getType();
        RectangleShape getColBox();
        void setPosition(int, int);

    protected:
    private:
        Animation *sprite;
        unsigned int type;
        RectangleShape *collision_box;

};

#endif // ENEMY_H
