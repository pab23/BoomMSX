#include "Game.h"

Game::Game(Vector2i dim)
{

    srand(NULL);
    //PARAMETROS
    winDim = dim;

    hud = new Hud();
    state = true;
    dead = false;

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
    elegido = rand() % 27;
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
    if(player->getHp() <= 0)
    {
        state = false;
    }
    escucharTeclado();
    if(dead)
    {
        elegido = rand() % enemies.size();
        dead = false;
        cout << elegido << endl;
    }
    else if(enemigoDentro())
    {
        elegido = rand() % enemies.size();
        cout << elegido <<endl;
    }

    disparoEnemigo();
    mueveEnemigos();
    mueveBalas();
    procesarColisiones();
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
                    if(j == elegido)
                        dead = true;
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
    if(enemies[elegido]->getBounds().intersects(player->getBounds()) && dmg_clock.getElapsedTime().asSeconds() < 2.f)
    {
        player->setVida(-DANO);
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
    Vector2f dir, normalizada;

    dir = player->getPosition() - enemies[elegido]->getPosition();
    normalizada.x = dir.x / sqrt(pow(dir.x, 2) + pow(dir.y, 2)) * 4;
    normalizada.y = dir.y / sqrt(pow(dir.x, 2) + pow(dir.y, 2)) * 4;
    if(enemies[elegido]->getPosition().y < player->getPosition().y -25)
        enemies[elegido]->move(normalizada, mili);
    else
        enemies[elegido]->move({0, 4}, mili);
    if(abs(enemies[elegido]->getPosition().x - player->getPosition().x) < 20 && enemy_cd.asSeconds() >= 1.f)
    {
        enemy_clock.restart();
        enemy_bullets.push_back(new Bullet(*sheet, enemies[elegido]->getPosition(), 10, 1));
    }

}

bool Game::enemigoDentro()
{

    if(enemies[elegido]->getPosition().y > winDim.y)
    {
        Enemy *auxEn = enemies[elegido];
        enemies.erase(enemies.begin()+elegido);
        delete auxEn;
        dead = true;
        return true;
    }
    return false;
}

