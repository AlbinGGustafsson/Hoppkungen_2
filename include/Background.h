#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "NonEventSprite.h"
#include <string>

namespace jengine {

    class Background: public NonEventSprite {
    public:
        static Background* getInstance(int x, int y, int w, int h, std::string imageFileName, std::string soundFileName, int volume);
        ~Background();

        void draw() const;
        void tick() {};
        void setBackground(std::string imageFileName);
        void setBackgroundSound(std::string imageFileName);
        Mix_Chunk* getBackgroundMusic() const;
        int getMusicVolume() const;

    protected:
        Background(int x, int y, int w, int h, std::string imageFileName, std::string soundFileName, int volume);

    private:
        SDL_Texture* bgTx;
        Mix_Chunk* backgroundSFX;
        int musicVolume;
    };

} // cwing

#endif
