#ifndef TERRAIN_H
#define TERRAIN_H
#include <SDL2/SDL.h>
#include "CollisionSprite.h"


namespace jengine {

    class Terrain: public CollisionSprite {
    public:
        static Terrain* getInstance(int x, int y, int w, int h, int blocks);

        void draw() const;
        void tick();

        ~Terrain();
    protected:
        Terrain(int x, int y, int w, int h, int blocks);

    private:

        SDL_Texture* terrainTx;
    };

} // jengine

#endif //TERRAIN_H
