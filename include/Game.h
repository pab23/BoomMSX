#ifndef GAME_H
#define GAME_H

#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include <ctime>

#include "SFML/Graphics.hpp"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Hud.h"

#define DANO 10
#define UPDATE_RATIO 1000/30

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
        void mueveEnemigos();
        void mueveBalas();
        void enemigoDentro();
        void restart();
        void muere(Enemy*);
        void elige();

    protected:

    private:

        RenderWindow *window;
        Texture *sheet, *bg;
        Sprite *bgSprite;
        vector<Bullet*> bullets, enemy_bullets;
        vector<Enemy*> enemies;
        Vector2i winDim;
        unsigned int score = 0, cont;
        Font *font;
        Text *scoreT;
        Clock bullet_clock, enemy_clock, game_clock, select_clock, dmg_clock, text_clock;
        Time bullet_cooldown, enemy_cd, game_timer, select_timer;
        bool dir = false, state, dead, god, alive, info;
        Player* player;
        Hud* hud;
        float mili;
        Enemy *elegido;
        vector<Sprite*> lifes;


};

#endif // GAME_H
