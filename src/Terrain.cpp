#include "Terrain.h"

namespace jengine {

    using namespace constants;

    Terrain::Terrain(int x, int y, int w, int h) : NonEventSprite(x, y, w, h) {}

    Terrain::~Terrain() {

    }

    void Terrain::collision(Sprite* other) {

        if (Player* p = dynamic_cast<Player*>(other)){

            //Ovanför
            if ((p->getYPosition() + p->getRect().h) <= (getYPosition() + MAX_PLAYER_DOWNWARD_VELOCITY)) {
                aboveCollision(p);
                return;
            }
                //under
            if (p->getYPosition() >= (getYPosition() + getRect().h - JUMP_VELOCITY)) {
                belowCollision(p);
                return;
            }
            //Vänster
            if (p->getXPosition() < (getXPosition() + getRect().w / 2)) {
                leftCollision(p);
                return;
            }
            //höger
            if (p->getXPosition() > (getXPosition() + getRect().w / 2)) {
                rightCollision(p);
                return;
            } else {
                //testar, kanske förhindrar mega-bugg-clipping, verkar som det :)
                //frågan är om denna ska kunna ovveridas.... Får se om det behövs.
                //var -25 innan
                p->setYPosition(p->getYPosition() + JUMP_VELOCITY);
                return;
            }
        }

    }

    void Terrain::aboveCollision(Player* p) {

        p->setYCollision(true);
        p->resetYVelocity();
        p->resetXVelocity();

        //anti clipping
        p->setYPosition(getRect().y + 1 - p->getRect().h);

    }

    void Terrain::belowCollision(Player* p) {

        if (p->getYVelocity() > -MIN_DOWNWARD_BOUNCE_VELOCITY) {
            p->setYVelocity(MIN_DOWNWARD_BOUNCE_VELOCITY);
        } else {
            p->setYVelocity(p->getYVelocity() < -MAX_DOWNWARD_BOUNCE_VELOCITY ?
                            MAX_DOWNWARD_BOUNCE_VELOCITY : -p->getYVelocity());
        }

    }

    void Terrain::leftCollision(Player* p) {

        p->setXPosition(p->getXPosition() - HORIZONTAL_MOVEMENT);
        p->setXVelocity(-(p->getXVelocity() / 2));
        p->setXCollision(true);
    }

    void Terrain::rightCollision(Player* p) {

        p->setXPosition(p->getXPosition() + HORIZONTAL_MOVEMENT);
        p->setXVelocity(-(p->getXVelocity() / 2));
        p->setXCollision(true);
    }


} // jengine