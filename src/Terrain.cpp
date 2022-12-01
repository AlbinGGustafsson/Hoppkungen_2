#include "Terrain.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace jengine {

    using namespace constants;

    Terrain *Terrain::getInstance(int x, int y, int w, int h, int blocks) {
        return new Terrain(x, y, w, h, blocks);
    }

    Terrain::Terrain(int x, int y, int w, int h, int blocks) : CollisionSprite(x, y, w, h) {

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

    void Terrain::draw() const {
        SDL_RenderCopy(sys.getRenderer(), terrainTx, nullptr, &rect);
    }

    void Terrain::tick() {
    }

    Terrain::~Terrain() {
        SDL_DestroyTexture(terrainTx);

    }

} // jengine