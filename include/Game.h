#ifndef GAME_H
#define GAME_H

#include <vector>

#include "SFML/Graphics.hpp"

#include "Bullet.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

class Game
{
    public:
        Game(Vector2i, float);

        void gameLoop();
        void dibujar();
        void escucharTeclado();
        void procesarColisiones();

    protected:

    private:

        RenderWindow *window;
        Texture *sheet, *bg;
        Sprite *bgSprite, *player;
        vector<Bullet> bullets;
        vector<Enemy> enemies;
        Vector2i winDim;
        float vel;


};

#endif // GAME_H
