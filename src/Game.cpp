#include "Game.h"

Game::Game(Vector2i dim, float kVel)
{
    //PARAMETROS
    winDim = dim;
    vel = kVel;

    //VENTANA

    window = new RenderWindow(VideoMode(dim.x, dim.y), "BoomMSX");
    window->setFramerateLimit(60);

    //HOJA TEXTURAS
    sheet = new Texture;
    sheet->loadFromFile("mySheet.png");

    //FONDO
    bg = new Texture;
    bg->loadFromFile("bg.png");
    bgSprite = new Sprite(*bg);
    bgSprite->scale(0.390625, 0.390625);

    //JUGADOR
    player = new Sprite(*sheet);
    player->setOrigin(17.5, 17.5);
    player->setTextureRect(sf::IntRect(0, 0, 35, 35));
    player->setPosition(390,520);

    //INICIALIZACION VARIABLES
    //enemies = new vector<Enemy>;
    //bullets = new vector<Bullet>;

    gameLoop();
}

void Game::gameLoop()
{
    while(window->isOpen())
    {
        escucharTeclado();
        dibujar();
    }
}

void Game::dibujar()
{
    window->clear();

    window->draw(*bgSprite);
    window->draw(*player);


    window->display();
}

void Game::escucharTeclado()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        bullets.push_back(Bullet(*sheet, player->getPosition().x, player->getPosition().y-26));
    }
    if(Keyboard::isKeyPressed(Keyboard::Q))
    {
        //printf("Bullets created: %d", (int)bullets.size());
        window->close();
    }
    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        if(player->getPosition().x < winDim.x-20)
        {
            player->move(vel, 0);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        if(player->getPosition().x > 20)
        {
            player->move(-vel, 0);
        }
    }/*
    for(unsigned z = 0; z < bullets.size(); z++ )
    {
        bullets[z].move();
    }*/
}

void Game::procesarColisiones()
{
    FloatRect barrier({0, 0}, {600, 0});


    for(unsigned i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].getBounds().intersects(barrier))
        {
//TO-DO
        }
    }
}
