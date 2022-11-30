#include "CollisionSprite.h"

namespace jengine {

    using namespace constants;

    CollisionSprite::CollisionSprite(int x, int y, int w, int h) : NonEventSprite(x, y, w, h) {}

    CollisionSprite::~CollisionSprite() {

    }

    void CollisionSprite::collision(Player *p) {

        //Ovanför
        if ((p->getYPosition() + p->getRect().h) <= (getYPosition() + MAX_PLAYER_DOWNWARD_VELOCITY)) {
            aboveCollision(p);
        }
            //under
        else if (p->getYPosition() >= (getYPosition() + getRect().h - JUMP_VELOCITY)) {
            belowCollision(p);
        } else {

            //Vänster
            if (p->getXPosition() < (getXPosition() + getRect().w / 2)) {
                leftCollision(p);
            }
                //höger
            else if (p->getXPosition() > (getXPosition() + getRect().w / 2)) {
                rightCollision(p);

                //testar, kanske förhindrar mega-bugg-clipping, verkar som det :)
                //frågan är om denna ska kunna ovveridas.... Får se om det behövs.
            } else {
                //var -25 innan
                p->setYPosition(p->getYPosition() + JUMP_VELOCITY);
            }
        }

    }

    void CollisionSprite::aboveCollision(Player* p) {

        p->setYCollision(true);
        p->resetYVelocity();
        p->resetXVelocity();

        //anti clipping
        p->setYPosition(getRect().y + 1 - p->getRect().h);

    }

    void CollisionSprite::belowCollision(Player* p) {

        if (p->getYVelocity() > -MIN_DOWNWARD_BOUNCE_VELOCITY) {
            p->setYVelocity(MIN_DOWNWARD_BOUNCE_VELOCITY);
        } else {
            p->setYVelocity(p->getYVelocity() < -MAX_DOWNWARD_BOUNCE_VELOCITY ?
                            MAX_DOWNWARD_BOUNCE_VELOCITY : -p->getYVelocity());
        }

    }

    void CollisionSprite::leftCollision(Player* p) {

        p->setXPosition(p->getXPosition() - HORIZONTAL_MOVEMENT);
        p->setXVelocity(-(p->getXVelocity() / 2));
        p->setXCollision(true);
    }

    void CollisionSprite::rightCollision(Player* p) {

        p->setXPosition(p->getXPosition() + HORIZONTAL_MOVEMENT);
        p->setXVelocity(-(p->getXVelocity() / 2));
        p->setXCollision(true);
    }


} // jengine