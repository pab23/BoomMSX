#include "Game.h"

Game::Game(Vector2i dim)
{

    srand(time(NULL));
    //PARAMETROS
    winDim = dim;

    hud = new Hud();
    state = true;
    cont = 0;

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
    alive = true;
    info = dead = god = false;
    creaEnemigos();
    elige();
    creaMarcador();
    gameLoop();
}

void Game::gameLoop()
{
    while(window->isOpen())
    {


        bullet_cooldown = bullet_clock.getElapsedTime();
        enemy_cd = enemy_clock.getElapsedTime();
        if(game_clock.getElapsedTime().asMilliseconds() >= UPDATE_RATIO)
        {
            game_timer = game_clock.restart();
            mili = min(1.f, float(game_timer.asMilliseconds())/UPDATE_RATIO);
            update();
        }



        dibujar();
    }
}

void Game::update()
{
    if((lifes.empty() && !alive) || enemies.size() == 0)
    {
        state = false;
    }

    escucharTeclado();
    if(state)
    {
        enemigoDentro();
        procesarColisiones();
        if(dead)
        {
            elige();
        }
        disparoEnemigo();
        mueveEnemigos();
        mueveBalas();

    }

}

void Game::dibujar()
{
    window->clear();
    window->draw(*bgSprite);
    if(!state)
    {
        window->draw(hud->textoMuerte());
        if(text_clock.getElapsedTime().asMilliseconds() >= 500)
        {
            window->draw(hud->subTextMuerte());
            if(text_clock.getElapsedTime().asMilliseconds() >= 1000)
                text_clock.restart();
        }
    }
    else
    {

        window->draw(player->getSprite());

        for(unsigned i = 0; i < enemies.size(); i++)
        {
            window->draw(enemies[i]->getSprite());
            if(info)
                window->draw(enemies[i]->getColBox());
        }
        for( unsigned j = 0; j < bullets.size(); j++)
        {
            window->draw(bullets[j]->getSprite());
            if(info)
                window->draw(bullets[j]->getColBox());
        }

        for( unsigned j = 0; j < enemy_bullets.size(); j++)
        {
            window->draw(enemy_bullets[j]->getSprite());
            if(info)
                window->draw(enemy_bullets[j]->getColBox());
        }

    }
    window->draw(*scoreT);
    for(unsigned i = 0; i < lifes.size(); i++)
        window->draw(*lifes[i]);

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
        if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::I))
        {
            info = !info;
        }
        if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::G))
        {
            god = !god;
            cout << "God mode: ";
            if(god)
                cout<< "Enabled";
            else
                cout<<"Disabled";
            cout<<endl;
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
            player->move(true, mili);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        if(player->getPosition().x > 20)
        {
            player->move(false, mili);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::R))
    {
        restart();
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
                    muere(enemies[j]);
                    score+= enemies[j]->getType()*10+10;
                    stringstream ss;
                    ss<<"SCORE "<<score;
                    scoreT->setString(ss.str().c_str());
                    break;
                }

            }
        }
    }
    for(unsigned i = 0; i < enemy_bullets.size(); i++)
    {
        if(enemy_bullets[i]->getBounds().intersects(player->getBounds()))
        {
            if(!god)
            {
                if(!lifes.empty())
                    lifes.erase(lifes.end()-1);
                else
                    alive = false;

                player->resetPosition();
            }

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
    if(elegido->getBounds().intersects(player->getBounds()) && dmg_clock.getElapsedTime().asSeconds() < 2.f)
    {
        if(!god)
        {
            if(!lifes.empty())
                lifes.erase(lifes.end()-1);
            else
                alive = false;

            player->resetPosition();
        }

        dmg_clock.restart();
    }

}

void Game::mueveEnemigos()
{
    bool down = false;
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
            enemies[i]->move({0, 4}, mili);
        down = false;
    }
    if(dir)
    {
        for( unsigned i = 0; i < enemies.size(); i++)
            enemies[i]->move({-1, 0}, mili);
    }
    else
    {
        for( unsigned i = 0; i < enemies.size(); i++)
            enemies[i]->move({1, 0}, mili);
    }
}

void Game::mueveBalas()
{
    for(unsigned z = 0; z < bullets.size(); z++ )
        bullets[z]->move(false, mili);
    for(unsigned z = 0; z < enemy_bullets.size(); z++ )
        enemy_bullets[z]->move(true, mili);
}

void Game::creaEnemigos()
{
    int cont = 0;


    int posX  = 100, posY = 100, type = 2;
    for( unsigned i = 0; i < 27; i++)
    {
        enemies.push_back(new Enemy(*sheet, type));
        enemies[i]->setPosition(posX, posY);
        posX += 75;
        if(posX > winDim.x-100)
        {
            type--;
            cont++;
            posX = 100;
            posY += 75;
        }
    }

}

void Game::creaMarcador()
{

    std::stringstream ss;
    ss <<"SCORE  "<< score;
    font = new Font;
    font->loadFromFile("ARCADE.TTF");
    scoreT = new Text(ss.str().c_str(), *font);
    scoreT->setCharacterSize(25);
    scoreT->setOrigin(125, 25);
    scoreT->setPosition(winDim.x/2, 570);

    for(unsigned i = 0; i < 2; i++)
    {
        lifes.push_back(new Sprite(player->getSprite()));
        lifes[i]->setPosition(45+(i*45), 570);
    }
}


void Game::disparoEnemigo()
{
    Vector2f dir, normalizada;

    dir = player->getPosition() - elegido->getPosition();
    normalizada.x = dir.x / sqrt(pow(dir.x, 2) + pow(dir.y, 2)) * 6;
    normalizada.y = dir.y / sqrt(pow(dir.x, 2) + pow(dir.y, 2)) * 4;
    if(elegido->getPosition().y < player->getPosition().y -30)
        elegido->move(normalizada, mili);
    else
        elegido->move({0, 4}, mili);
    if(abs(elegido->getPosition().x - player->getPosition().x) < 20 && enemy_cd.asSeconds() >= 1.f)
    {
        enemy_clock.restart();
        enemy_bullets.push_back(new Bullet(*sheet, elegido->getPosition(), 10, 1));
    }

}

void Game::enemigoDentro()
{

    if(elegido->getPosition().y > winDim.y)
    {
        muere(elegido);
    }
}

void Game::restart()
{
    while(enemies.size() != 0)
    {
        Enemy *auxEn = enemies[0];
        enemies.erase(enemies.begin());
        delete auxEn;
    }
    while(enemy_bullets.size() != 0)
    {
        Bullet *aux = enemy_bullets[0];
        enemy_bullets.erase(enemy_bullets.begin());
        delete aux;
    }
    while( bullets.size() != 0)
    {
        Bullet *aux = bullets[0];
        bullets.erase(bullets.begin());
        delete aux;
    }
    while( lifes.size() != 0)
    {
        Sprite *aux = lifes[0];
        lifes.erase(lifes.begin());
        delete aux;
    }
    creaEnemigos();
    score = 0;
    creaMarcador();
    state = true;
    alive = true;
    elige();
}

void Game::muere(Enemy* j)
{

    for(unsigned i = 0; i < enemies.size(); i++)
    {
        if(enemies[i] == j)
        {
            enemies.erase(enemies.begin()+ i);
            break;
        }
    }
    if(j == elegido)
    {
        dead = true;
        elige();
    }
    delete j;
}

void Game::elige()
{
    if(enemies.size() != 0)
    elegido = enemies[rand() % enemies.size()];
    dead = false;
}

