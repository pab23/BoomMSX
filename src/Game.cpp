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
    creaEnemigos();
    creaMarcador();
    gameLoop();
}

void Game::gameLoop()
{
    while(window->isOpen())
    {
        bullet_cooldown = bullet_clock.getElapsedTime();
        escucharTeclado();
        procesarColisiones();
        dibujar();
    }
}

void Game::dibujar()
{
    window->clear();

    window->draw(*bgSprite);
    window->draw(*player);
    window->draw(*scoreT);
    for(unsigned i = 0; i < enemies.size(); i++)
        window->draw(enemies[i].getSprite());
    for( unsigned j = 0; j < bullets.size(); j++)
        window->draw(bullets[j].getSprite());
    window->display();
}

void Game::escucharTeclado()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bullet_cooldown.asSeconds() >= .5f)
    {
        bullet_clock.restart();
        bullets.push_back(Bullet(*sheet, player->getPosition().x, player->getPosition().y-26));
    }
    if(Keyboard::isKeyPressed(Keyboard::Q))
    {
        printf("Bullets created: %d", (int)bullets.size());
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
    }
    for(unsigned z = 0; z < bullets.size(); z++ )
    {
        bullets[z].move();
    }
}

void Game::procesarColisiones()
{
    FloatRect barrier({-30, 0}, {600, 1});


    for(unsigned i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].getBounds().intersects(barrier))
        {
            bullets.erase(bullets.begin()+i);
        }
    }
}

void Game::creaEnemigos()
{
    Sprite ex(*sheet);
    ex.setTextureRect(IntRect(35,0, 32, 32));
    ex.rotate(-90);
    ex.setScale(1.25, 1.5);
    ex.setOrigin(16, 16);

    int posX  = 150, posY = 100;
    for( int i = 0; i < 12; i++){
        ex.setPosition(posX , posY);
        Enemy aux(ex, 1, 0);
        enemies.push_back(aux);
        posX += 100;
        if(posX >= winDim.x-50){
            posX = 150;
            posY += 100;
        }

    }
}

void Game::creaMarcador()
{

    std::stringstream ss;
    ss <<"SCORE: "<< score;
    font = new Font;
    font->loadFromFile("ARCADE.TTF");
    scoreT = new Text(ss.str().c_str(), *font);
    scoreT->setCharacterSize(25);
    scoreT->setOrigin(0, 25);
    scoreT->setPosition(30, 570);
}
