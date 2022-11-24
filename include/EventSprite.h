#ifndef EVENTSPRITE_H
#define EVENTSPRITE_H
#include <SDL2/SDL.h>
#include "Sprite.h"

namespace jengine {


    class EventSprite: public Sprite {
    public:

        virtual void mouseDown(const SDL_Event &event) {};

        virtual void mouseUp(const SDL_Event &event) {};

        virtual void KeyDown(const SDL_Event &event) {};

        virtual void KeyUp(const SDL_Event &event) {};

    protected:
        EventSprite(int x, int y, int w, int h);

    };
}

#endif
