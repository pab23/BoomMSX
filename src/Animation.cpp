#include "Animation.h"

Animation::Animation(int type, Texture& tex)
{
    int aux, spacing = 32;
    Vector2f sp_size = Vector2f(spacing, spacing);
    switch(type)
    {
    case 0:
        aux = 35+32*2;
        break;
    case 1:
        aux = 35*32;
        break;
    case 2:
        aux = 35;
        break;
    default:
        aux = 0;
        break;
    }
    for(unsigned i = 0; i < 6; i++)
    {
        sprite_array.push_back(new Sprite(tex));
        sprite_array[i]->setTextureRect(IntRect(aux, spacing*i, spacing, spacing));
        sprite_array[i]->rotate(-90);
        sprite_array[i]->setScale(1.25, 1.5);
        sprite_array[i]->setOrigin(16, 16);
    }
    current = 0;
}

Animation::~Animation()
{
    while( sprite_array.size() != 0)
    {
        Sprite *aux = sprite_array[0];
        sprite_array.erase(sprite_array.begin());
        delete aux;
    }
}

void Animation::move(Vector2f dir, float time, int speed)
{
    for(unsigned i = 0; i < sprite_array.size(); i++)
    {
        sprite_array[i]->move(dir.x * speed * time * 1000, dir.y * speed * time * 1000);
    }
}

void Animation::update()
{
    if(current < sprite_array.size()-2)
        current++;
    else
        current = 0;
}

Sprite Animation::getCurrent()
{
    return *sprite_array[current];
}
Vector2f Animation::getPosition()
{
    return sprite_array[0]->getPosition();
}
void Animation::setPosition(int x, int y)
{
    for(unsigned i = 0; i < sprite_array.size(); i++)
    {
        sprite_array[i]->setPosition(x, y);
    }
}


