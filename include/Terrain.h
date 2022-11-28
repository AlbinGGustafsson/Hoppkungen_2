#ifndef TERRAIN_H
#define TERRAIN_H
#include "NonEventSprite.h"
#include <SDL2/SDL.h>


namespace jengine {

    class Terrain: public NonEventSprite {
    public:
        static Terrain* getInstance(int x, int y, int w, int h, int blocks);
        bool isCollidable();

        void draw() const;
        void tick();

        int getXPosition();
        int getYPosition();

        ~Terrain();
    protected:
        Terrain(int x, int y, int w, int h, int blocks);

    private:

        SDL_Texture* terrainTx;

        bool collidable;
    };

} // jengine

#endif //TERRAIN_H
