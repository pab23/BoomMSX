#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Game
{
    public:
        Game(int, int);

        void gameLoop();
        void draw();

    protected:

    private:

        RenderWindow *window;
        Texture *sheet, *bg;
        Sprite *bgSprite;

};

#endif // GAME_H
