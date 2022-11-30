#include "Terrain.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace jengine {

    using namespace constants;

    Terrain *Terrain::getInstance(int x, int y, int w, int h, int blocks) {
        return new Terrain(x, y, w, h, blocks);
    }

    Terrain::Terrain(int x, int y, int w, int h, int blocks) : CollisionSprite(x, y, w, h) {

        if (blocks == 1) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/single.png").c_str());
        } else if (blocks == 2) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/double.png").c_str());
        } else if (blocks == 3) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/triple.png").c_str());
        } else {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/single.png").c_str());
        }
    }

    void Terrain::draw() const {
        SDL_RenderCopy(sys.getRenderer(), terrainTx, nullptr, &rect);
    }

    void Terrain::tick() {
        SDL_RenderCopy(sys.getRenderer(), terrainTx, nullptr, &rect);
    }

    Terrain::~Terrain() {
        SDL_DestroyTexture(terrainTx);

    }

    void Terrain::collision(Player *p) {

        //Ovanför
        if ((p->getYPosition() + p->getRect().h) <= (getYPosition() + MAX_PLAYER_DOWNWARD_VELOCITY)) {

            p->setYCollision(true);
            p->resetYVelocity();
            p->resetXVelocity();

            //anti clipping
            p->setYPosition(getRect().y + 1 - p->getRect().h);
        }
            //under
        else if (p->getYPosition() >= (getYPosition() + getRect().h - JUMP_VELOCITY)) {

            if (p->getYVelocity() > -MIN_DOWNWARD_BOUNCE_VELOCITY) {
                p->setYVelocity(MIN_DOWNWARD_BOUNCE_VELOCITY);
            } else {
                p->setYVelocity(p->getYVelocity() < -MAX_DOWNWARD_BOUNCE_VELOCITY ?
                                MAX_DOWNWARD_BOUNCE_VELOCITY : -p->getYVelocity());
            }

        } else {

            //Vänster
            if (p->getXPosition() < (getXPosition() + getRect().w / 2)) {
                p->setXPosition(p->getXPosition() - HORIZONTAL_MOVEMENT);
                p->setXVelocity(-(p->getXVelocity() / 2));
                p->setXCollision(true);
            }
                //höger
            else if (p->getXPosition() > (getXPosition() + getRect().w / 2)) {
                p->setXPosition(p->getXPosition() + HORIZONTAL_MOVEMENT);
                p->setXVelocity(-(p->getXVelocity() / 2));
                p->setXCollision(true);
            } else {
                //testar, kanske förhindrar mega-bugg-clipping, verkar som det :)
                //var -25 innan
                p->setYPosition(p->getYPosition() + JUMP_VELOCITY);
            }
        }


    }


} // jengine