#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#define SPEED 0.5

using namespace sf;

class Enemy
{
    public:
        Enemy(){ type = 0;};
        Enemy(Sprite, int);
        virtual ~Enemy();

        void hit();
        void move(Vector2f, float);


        Sprite getSprite();
        Vector2f getPosition();
        FloatRect getBounds();
        int getType();
        RectangleShape getColBox();

    protected:
    private:
        Sprite *sprite;
        unsigned int type;
        RectangleShape *collision_box;

};

#endif // ENEMY_H
