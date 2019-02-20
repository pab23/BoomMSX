#include "Game.h"

Game::Game(int ancho, int alto)
{
    //VENTANA
    window = new RenderWindow(VideoMode(ancho, alto), "BoomMSX");
    window->setFramerateLimit(60);

    //HOJA TEXTURAS
    sheet = new Texture;
    sheet->loadFromFile("mySheet.png");

    //FONDO
    bg = new Texture;
    bg->loadFromFile("bg.png");
    bgSprite = new Sprite;
    bgSprite->setTexture(*bg);
    bgSprite->scale(0.390625, 0.390625);
}

void Game::gameLoop()
{
    while(window->isOpen())
    {

    }
}

void Game::draw()
{
    window->clear();

    window->display();
}

