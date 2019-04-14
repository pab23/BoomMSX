#ifndef GAME_H
#define GAME_H

#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Hud.h"

#define DANO 10

using namespace sf;
using namespace std;

class Game
{
    public:
        Game(Vector2i);

        void gameLoop();
        void dibujar();
        void escucharTeclado();
        void procesarColisiones();
        void creaEnemigos();
        void creaMarcador();
        void update();
        void disparoEnemigo();
        void colisionJugador();

    protected:

    private:

        RenderWindow *window;
        Texture *sheet, *bg;
        Sprite *bgSprite;
        vector<Bullet*> bullets, enemy_bullets;
        vector<Enemy*> enemies;
        Vector2i winDim;
        unsigned int score = 0;
        Font *font;
        Text *scoreT;
        Clock bullet_clock, enemy_clock;
        Time bullet_cooldown, enemy_cd;
        bool dir = false, state;
        Player* player;
        Hud* hud;


};

#endif // GAME_H
