#include "Hud.h"

Hud::Hud()
{
    fuente = new Font;
    fuente->loadFromFile("ARCADE.TTF");
}

Hud::~Hud()
{
    //dtor
}

Text Hud::textoMuerte()
{
    Text* dead = new Text("GAME OVER", *fuente);
    dead->setCharacterSize(40);
    dead->setOrigin(dead->getGlobalBounds().width/2, dead->getGlobalBounds().height/2);
    dead->setPosition(400, 300);

    return *dead;
}
Text Hud::subTextMuerte()
{
    Text* dead = new Text("Press R to restart", *fuente);
    dead->setCharacterSize(20);
    dead->setOrigin(dead->getGlobalBounds().width/2, dead->getGlobalBounds().height/2);
    dead->setPosition(400, 340);
    return *dead;
}
