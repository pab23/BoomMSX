#ifndef HUD_H
#define HUD_H


#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Hud
{
    public:
        Hud();
        virtual ~Hud();

        Text textoMuerte();

    private:

    Font* fuente;

};

#endif // HUD_H
