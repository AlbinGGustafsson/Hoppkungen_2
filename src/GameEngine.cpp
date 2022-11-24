#include "GameEngine.h"
#include "System.h"
#include <SDL2/SDL.h>
#include "EventSprite.h"

namespace jengine {

    void GameEngine::add(Sprite *s) {
        added.push_back(s);
    }

    void GameEngine::remove(Sprite *s) {
        removed.push_back(s);
    }

    void GameEngine::run() {
        Uint32 tickInterval = 1000 / FPS;

        bool running = true;
        while (running) {

            Uint32 nextTick = SDL_GetTicks() + tickInterval;

            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: {
                        running = false;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        for (Sprite *s: sprites) {
                            if (auto e = dynamic_cast<EventSprite *>(s)) {
                                e->mouseDown(event);
                            }
                        }
                        break;
                    }
                    case SDL_MOUSEBUTTONUP: {
                        for (Sprite *s: sprites) {
                            if (auto e = dynamic_cast<EventSprite *>(s)) {
                                e->mouseUp(event);
                            }
                        }
                        break;
                    }
                    case SDL_KEYDOWN: {
                        for (Sprite *s: sprites) {
                            if (auto e = dynamic_cast<EventSprite *>(s)) {
                                e->KeyDown(event);
                            }
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        for (Sprite *s: sprites) {
                            if (auto e = dynamic_cast<EventSprite *>(s)) {
                                e->KeyUp(event);
                            }
                        }
                        break;
                    }
                }//switch
            }//inre while

            for (Sprite *s: added) {
                sprites.push_back(s);
            }
            added.clear();

            for (Sprite *s: removed) {
                for (auto i = sprites.begin(); i != sprites.end();) {
                    if (*i == s) {
                        i = sprites.erase(i);
                    } else {
                        i++;
                    }
                }
            }
            removed.clear();


            for (Sprite *s: sprites) {
                s->tick();
            }

            SDL_SetRenderDrawColor(sys.getRenderer(), 255, 255, 255, 255);
            SDL_RenderClear(sys.getRenderer());
            for (Sprite *s: sprites) {
                s->draw();
            }
            SDL_RenderPresent(sys.getRenderer());

            //räknar ut om det finns en delay till nästa tick.
            int delay = nextTick - SDL_GetTicks();

            //om det finns en delay till nästa tick, sätt en delay
            if (delay > 0) {
                SDL_Delay(delay);
            }


        }//yttre while
    }


    GameEngine::~GameEngine() {

    }

}

