#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#define BULLET_SPEED 6

using namespace sf;
using namespace std;

class Bullet
{
    public:
        Bullet(Texture&, Vector2f, int, int);
        FloatRect getBounds();
        ~Bullet();

        void move(bool, float);
        void rotate();

        Sprite getSprite();
        Vector2f getPos();
        int getDmg();

    protected:

    private:
        Sprite* sprite;
        int dmg;
};

#endif // BULLET_H
