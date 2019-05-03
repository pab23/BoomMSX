#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"


using namespace std;
using namespace sf;

class Animation
{
    public:
        Animation(int, Texture&);
        virtual ~Animation();

        void update();
        void move(Vector2f, float, int);

        Vector2f getPosition();
        Sprite getCurrent();
        void setPosition(int, int);

    protected:

    private:
        vector<Sprite*> sprite_array;
        int current;

};

#endif // ANIMATION_H
