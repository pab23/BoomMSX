#include "Game.h"

Game::Game(Vector2i dim)
{
    //PARAMETROS
    winDim = dim;

    hud = new Hud();
    state = true;

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
    player = new Player(*sheet);

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
        enemy_cd = enemy_clock.getElapsedTime();
        update();


        dibujar();
    }
}

void Game::update()
{
    if(player->getHp() <= 0)
    {
        state = false;
    }
    bool down = false;;
    escucharTeclado();
    disparoEnemigo();
    procesarColisiones();
    for(unsigned z = 0; z < bullets.size(); z++ )
        bullets[z]->move(false);
    for(unsigned z = 0; z < enemy_bullets.size(); z++ )
        enemy_bullets[z]->move(true);
    for(unsigned i = 0; i < enemies.size(); i++)
    {
        if(enemies[i]->getPosition().x >= winDim.x-25)
        {
            dir = true;
            down = true;
        }
        else if(enemies[i]->getPosition().x < 25)
        {
            dir = false;
            down = true;
        }
    }
    if(down)
    {
        for( unsigned i = 0; i < enemies.size(); i++)
            enemies[i]->move({0, 4});
        down = false;
    }
    if(dir)
    {
        for( unsigned i = 0; i < enemies.size(); i++)
            enemies[i]->move({-1, 0});
    }
    else
    {
        for( unsigned i = 0; i < enemies.size(); i++)
            enemies[i]->move({1, 0});
    }
}

void Game::dibujar()
{
    window->clear();

    window->draw(*bgSprite);
    window->draw(player->getSprite());
    window->draw(*scoreT);
    if(!state)
        window->draw(hud->textoMuerte());

    for(unsigned i = 0; i < enemies.size(); i++)
        window->draw(enemies[i]->getSprite());

    for( unsigned j = 0; j < bullets.size(); j++)
        window->draw(bullets[j]->getSprite());
    for( unsigned j = 0; j < enemy_bullets.size(); j++)
        window->draw(enemy_bullets[j]->getSprite());

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
        bullets.push_back(new Bullet(*sheet, {player->getPosition().x, player->getPosition().y-26}, DANO, 0));
    }
    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        if(player->getPosition().x < winDim.x-20)
        {
            player->move(true);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        if(player->getPosition().x > 20)
        {
            player->move(false);
        }
    }

}

void Game::procesarColisiones()
{
    FloatRect barrier({-30, 0}, {winDim.x, 1});


    for(unsigned i = 0; i < bullets.size(); i++)
    {
        if(bullets[i]->getPos().y < 0)
        {
            Bullet *aux = bullets[i];
            bullets.erase(bullets.begin()+i);
            delete aux;
        }
        else
        {
            for( unsigned j = 0; j < enemies.size(); j++)
            {

                if(bullets[i]->getBounds().intersects(enemies[j]->getSprite().getGlobalBounds()))
                {

                    Bullet *aux = bullets[i];
                    bullets.erase(bullets.begin()+i);
                    delete aux;
                    Enemy *auxEn = enemies[j];
                    enemies.erase(enemies.begin()+j);
                    delete auxEn;
                    score++;
                    stringstream ss;
                    ss<<"SCORE: "<<score;
                    scoreT->setString(ss.str().c_str());
                }

            }
        }
    }
    for(unsigned i = 0; i < enemy_bullets.size(); i++)
    {
        if(enemy_bullets[i]->getBounds().intersects(player->getBounds()))
        {
            player->setVida(-enemy_bullets[i]->getDmg());
            Bullet *aux = enemy_bullets[i];
            enemy_bullets.erase(enemy_bullets.begin()+i);
            delete aux;
        }
        else if(enemy_bullets[i]->getPos().y > winDim.y)
        {
            Bullet *aux = enemy_bullets[i];
            enemy_bullets.erase(enemy_bullets.begin()+i);
            delete aux;
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
        enemies.push_back(new Enemy(ex, 1, 0));
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


void Game::disparoEnemigo()
{
    for(unsigned i = 0; i < enemies.size(); i++)
    {
        if(abs(enemies[i]->getPosition().x - player->getPosition().x) < 5 && enemy_cd.asSeconds() >= 2)
        {
            enemy_clock.restart();
            enemy_bullets.push_back(new Bullet(*sheet, enemies[i]->getPosition(), 10, 1));

        }

    }
    cout<<"balas: "<<enemy_bullets.size()<<endl;
}

