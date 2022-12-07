#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "NonEventSprite.h"
#include "Player.h"

namespace jengine {

    class Terrain : public NonEventSprite {

    public:

    protected:
        Terrain(int x, int y, int w, int h);

    public:
        void collision(Sprite* other) override;
        virtual void aboveCollision(Player* p);
        virtual void belowCollision(Player* p);
        virtual void leftCollision(Player* p);
        virtual void rightCollision(Player* p);


        virtual ~Terrain();

    private:

    };

}

#endif
