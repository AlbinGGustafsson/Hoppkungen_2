#include "Game/StoneTerrain.h"
#include "Constants.h"
#include "jEngine/System.h"
#include <SDL2/SDL_image.h>

namespace jengine {

    using namespace constants;

    StoneTerrain *StoneTerrain::getInstance(int x, int y, int w, int h) {
        return new StoneTerrain(x, y, w, h);
    }

    StoneTerrain::StoneTerrain(int x, int y, int w, int h) : Terrain(x, y, w, h) {

        terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/stone.png").c_str());
    }

    void StoneTerrain::draw() const {
        SDL_RenderCopy(sys.getRenderer(), terrainTx, nullptr, &getRect());
    }

    void StoneTerrain::tick() {
    }

    StoneTerrain::~StoneTerrain() {
        SDL_DestroyTexture(terrainTx);

    }

} // jengine