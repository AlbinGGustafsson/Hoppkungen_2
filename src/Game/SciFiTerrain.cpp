#include "Game/SciFiTerrain.h"
#include "Constants.h"
#include "jEngine/System.h"
#include <SDL2/SDL_image.h>

namespace jengine {

    using namespace constants;

    SciFiTerrain *SciFiTerrain::getInstance(int x, int y, int w, int h, int blocks) {
        return new SciFiTerrain(x, y, w, h, blocks);
    }

    SciFiTerrain::SciFiTerrain(int x, int y, int w, int h, int blocks) : Terrain(x, y, w, h) {

        if (blocks == 1) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/single.png").c_str());
        } else if (blocks == 2) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/double.png").c_str());
        } else if (blocks == 3) {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/triple.png").c_str());
        } else {
            terrainTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/terrain/single.png").c_str());
        }
    }

    void SciFiTerrain::draw() const {
        SDL_RenderCopy(sys.getRenderer(), terrainTx, nullptr, &getRect());
    }

    void SciFiTerrain::tick() {
    }

    SciFiTerrain::~SciFiTerrain() {
        SDL_DestroyTexture(terrainTx);

    }

} // jengine