#ifndef TERRAIN_H
#define TERRAIN_H
#include <SDL2/SDL.h>
#include "jEngine/Terrain.h"


namespace jengine {

    class SciFiTerrain: public Terrain {
    public:
        static SciFiTerrain* getInstance(int x, int y, int w, int h, int blocks);

        void draw() const override;
        void tick() override;

        ~SciFiTerrain();
    protected:
        SciFiTerrain(int x, int y, int w, int h, int blocks);

    private:

        SDL_Texture* terrainTx;
    };

} // jengine

#endif //TERRAIN_H
