#include "../include/Background.h"
#include "../include/Constants.h"
#include "../include/System.h"
#include <SDL2/SDL_image.h>
#include <string>



namespace jengine {
    Background::Background(int x, int y, int w, int h, std::string imageFileName, std::string soundFileName, int volume) : NonEventSprite(x, y, w, h) {

        //bgTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/backgrounds/bg1.png").c_str());
        musicVolume = volume;
        setBackground(imageFileName);
        setBackgroundSound(soundFileName);
    }

    Background *Background::getInstance(int x, int y, int w, int h,  std::string imageFileName, std::string soundFileName, int volume) {
        return new Background(x, y, w, h,imageFileName, soundFileName, volume);
    }

    void Background::draw() const {
        SDL_RenderCopy(sys.getRenderer(), bgTx, nullptr, nullptr);
    }

    void Background::setBackground(std::string imageFileName) {
        bgTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/backgrounds/" + imageFileName).c_str());
    }

    void Background::setBackgroundSound(std::string soundFileName) {
        backgroundSFX = Mix_LoadWAV((constants::gResPath + "sounds/" + soundFileName).c_str());
    }

    Mix_Chunk* Background::getBackgroundMusic() const{
        return backgroundSFX;
    }

    int Background::getMusicVolume() const{
        return musicVolume;
    }

    Background::~Background(){
        SDL_DestroyTexture(bgTx);
    }

}