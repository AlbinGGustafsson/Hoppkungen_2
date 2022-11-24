#ifndef NONEVENTSPRITE_H
#define NONEVENTSPRITE_H
#include "Sprite.h"

namespace jengine {
    class NonEventSprite : public Sprite {
    public:
        bool isCollidable() const;

    protected:
        NonEventSprite(int x, int y, int w, int h);

    private:
        bool collidable;
    };
}


#endif
