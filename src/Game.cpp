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

    //bullets = new vector<Bullet>(;
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
        //enemies.move();
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
    Event event;
    while( window->pollEvent(event))
    {
        if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Q))
        {
            window->close();
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::Space) && bullet_cooldown.asSeconds() >= .4f)
    {
        bullet_clock.restart();
        bullets.push_back(Bullet(*sheet, player->getPosition().x, player->getPosition().y-26));
    }
    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        if(player->getPosition().x < winDim.x-20)
        {
            player->move(vel, 0);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::A))
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
    FloatRect barrier({-30, 0}, {winDim.x, 1});


    for(unsigned i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].getBounds().intersects(barrier))
        {
            bullets.erase(bullets.begin()+i);
        }
        else
        {
            for( unsigned j = 0; j < enemies.size(); j++)
            {

                if(bullets[i].getBounds().intersects(enemies[j].getSprite().getGlobalBounds()))
                {
                    bullets.erase(bullets.begin()+i);
                    enemies.erase(enemies.begin()+j);
                    score++;
                    stringstream ss;
                    ss<<"SCORE: "<<score;
                    scoreT->setString(ss.str().c_str());
                }

            }
        }
    }
}

void Game::creaEnemigos()
{
    Sprite ex(*sheet);
    vector<IntRect> guides;
    guides.push_back(IntRect(35, 0, 32, 32));
    guides.push_back(IntRect(35+32, 0, 32, 32));
    guides.push_back(IntRect(2*32+35, 0, 32, 32));

    int cont = 0;


    ex.rotate(-90);
    ex.setScale(1.25, 1.5);
    ex.setOrigin(16, 16);

    int posX  = 100, posY = 100;
    for( unsigned i = 0; i < 27; i++)
    {
        ex.setPosition(posX , posY);
        ex.setTextureRect(guides[cont]);
        Enemy aux(ex, 1, 0);
        enemies.push_back(aux);
        posX += 75;
        if(posX > winDim.x-100)
        {
            cont++;
            posX = 100;
            posY += 75;
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
