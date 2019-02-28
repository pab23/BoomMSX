#ifndef GAME_H
#define GAME_H

#include <vector>
#include <sstream>
#include <iostream>

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
        void creaEnemigos();
        void creaMarcador();
        void update();

    protected:

    private:

        RenderWindow *window;
        Texture *sheet, *bg;
        Sprite *bgSprite, *player;
        vector<Bullet> bullets;
        vector<Enemy> enemies;
        Vector2i winDim;
        float vel;
        unsigned int score = 0;
        Font *font;
        Text *scoreT;
        Clock bullet_clock;
        Time bullet_cooldown;
        bool dir = false;


};

#endif // GAME_H
