#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "NonEventSprite.h"
#include <string>

namespace jengine {

    class Background: public NonEventSprite {
    public:
        static Background* getInstance(int x, int y, int w, int h);
        ~Background();

        void draw() const;
        void tick() {};
        void changeBackground(std::string imageFileName);

    protected:
        Background(int x, int y, int w, int h);

    private:
        SDL_Texture* bgTx;

    };

} // cwing

#endif
