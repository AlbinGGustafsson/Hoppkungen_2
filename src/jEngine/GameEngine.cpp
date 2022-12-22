#include "GameEngine.h"
#include "System.h"
#include <SDL2/SDL.h>
#include "EventSprite.h"
#include "Background.h"
#include "Constants.h"

using namespace constants;

namespace jengine {

    void GameEngine::add(Sprite *s) {
        added.push_back(s);
    }

    void GameEngine::remove(Sprite *s) {
        removed.push_back(s);
    }


    void GameEngine::run() {
        Uint32 tickInterval = 1000 / constants::FPS;
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
                                e->keyDown(event);
                                hotkey(event);
                            }
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        for (Sprite *s: sprites) {
                            if (auto e = dynamic_cast<EventSprite *>(s)) {
                                e->keyUp(event);
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


            //anropa alla sprite objekts checkCollision med alla andra sprites
            for (Sprite *s: sprites){
                s->gravity();
                for (Sprite *s2 : sprites){
                    if (s != s2){
                        s->checkCollision(s2);
                    }
                }
            }

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

    void GameEngine::setLevel(std::vector<Sprite *> level) {
        sprites = level;
        for(Sprite* s: sprites){
            if(Background *bg = dynamic_cast<Background *>(s)){
                Mix_PlayChannel(MUSIC_CHANNEL,bg->getBackgroundMusic() , -1);
                Mix_Volume(MUSIC_CHANNEL, bg->getMusicVolume());
            }
        }
    }

    void GameEngine::changeSFXVolume(int volume) const{
        Mix_Volume(JUMP_CHARGE_CHANNEL, volume);
        Mix_Volume(JUMP_CHANNEL, volume);
        Mix_Volume(WALKING_CHANNEL, volume);
    }


    void GameEngine::hotkey(SDL_Event& event) {
        for (auto entry : hotkeyFunctionMap){
            if (event.key.keysym.sym == entry.first){
                entry.second();
            }
        }
    }

    void GameEngine::addHotkey(hotkeyFunction f, SDL_Keycode k) {
        hotkeyFunctionMap.insert(std::make_pair(k, f));
    }
}

