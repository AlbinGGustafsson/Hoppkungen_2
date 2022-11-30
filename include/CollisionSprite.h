#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "NonEventSprite.h"
#include "Player.h"

namespace jengine {

    class CollisionSprite : public NonEventSprite {

    public:

    protected:
        CollisionSprite(int x, int y, int w, int h);

    public:
        virtual void collision(Player *player) {}

        virtual ~CollisionSprite();

    private:

    };

}

#endif
