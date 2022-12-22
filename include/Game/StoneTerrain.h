#ifndef TERRAIN_H
#define TERRAIN_H
#include <SDL2/SDL.h>
#include "jEngine/Terrain.h"


namespace jengine {

    class StoneTerrain: public Terrain {
    public:
        static StoneTerrain* getInstance(int x, int y, int w, int h);

        void draw() const override;
        void tick() override;

        ~StoneTerrain();
    protected:
        StoneTerrain(int x, int y, int w, int h);

    private:

        SDL_Texture* terrainTx;
    };

} // jengine

#endif //TERRAIN_H
