#include "GameEngine.h"
#include "System.h"
#include <SDL2/SDL.h>
#include "EventSprite.h"
#include "Player.h"
#include "Terrain.h"
#include <iostream>

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
                                e->keyDown(event);
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


            //Vi hade en bugg att den körde p->changeYVelocity(1); så många Terrains vi har i sprites.
            //just nu har vi en temporär lösningen som bevisade att detta var problemet.
            //men vi måste hitta en lösning på riktigt.


            //player collision
            for (Sprite *s: sprites) {
                if (Player *p = dynamic_cast<Player *>(s)) {

                    if (p->getYVelocity() < 15) {
                        //std::cout << counter << sprites.size() << std::endl;
                            p->changeYVelocity(1);

                    }
                    p->setYCollision(false);



                    for (Sprite *sp: sprites) {
                        if (Terrain *t = dynamic_cast<Terrain *>(sp)) {
                            if (SDL_HasIntersection(&p->getRect(), &t->getRect())) {

                                //haha... ett försök men man kan clippa in i hörnen och "fastna"

                                //std::cout << "px+pw: " << (p->getXPosition() + p->getRect().w) << "tx + 15: " << t->getXPosition() + 15;

                                //Ovanför
                                if ((p->getYPosition() + p->getRect().h) <= (t->getYPosition() + 15)) {
                                    //std::cout << "py + h: " << (p->getYPosition() + p->getRect().h) << " ty + 16 " << (t->getYPosition() + 16) << std::endl;
                                    p->setYCollision(true);
                                    p->resetYVelocity();
                                    p->resetXVelocity();
                                    //break;
                                }
                                //under
                                else if (p->getYPosition() >= (t->getYPosition() + t->getRect().h - 25)){
                                    //p->setYPosition(p->getYPosition() + 50);
                                    p->resetYVelocity();
                                    p->changeYVelocity(5);
//                                    p->changeYVelocity(-p->getYVelocity()*2);
                                    //break;
                                }else{
                                    std::cout << "else" << std::endl;

                                    //Vänster
                                    if (p->getXPosition() < (t->getXPosition() + t->getRect().h/2)){
                                        p->setXPosition(p->getXPosition() - 30);
                                        p->resetXVelocity();
                                        p->changeYVelocity(-(p->getYVelocity()/2));
                                    }
                                    //höger
                                    else if (p->getXPosition() > (t->getXPosition() + t->getRect().h/2)){
                                        p->setXPosition(p->getXPosition() + 30);
                                        p->resetXVelocity();
                                        p->changeYVelocity(-(p->getYVelocity()/2));
                                    }else{
                                        //testar, kanske förhindrar clipping
                                        p->setYPosition(p->getYPosition() - 25);
                                    }

                                    //break;
                                }

                            }

                        }
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

    }

}

