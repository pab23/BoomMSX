#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#define SPEED 0.5

using namespace sf;

class Enemy
{
    public:
        Enemy(){hp = 1; type = 0;};
        Enemy(Sprite, int, int);
        virtual ~Enemy();

        void hit();
        void move(Vector2f, float);

        Sprite getSprite();
        Vector2f getPosition();
        FloatRect getBounds();

    protected:
    private:
        Sprite *sprite;
        unsigned int hp;
        unsigned int type;

};

#endif // ENEMY_H
