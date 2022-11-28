#include "Background.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>


namespace jengine {
    Background::Background(int x, int y, int w, int h) : NonEventSprite(x, y, w, h) {

        bgTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/backgrounds/bg1.png").c_str());
    }

    Background *Background::getInstance(int x, int y, int w, int h) {
        return new Background(x, y, w, h);
    }

    void Background::draw() const {
        SDL_RenderCopy(sys.getRenderer(), bgTx, nullptr, nullptr);
    }

    Background::~Background(){
        SDL_DestroyTexture(bgTx);
    }

}