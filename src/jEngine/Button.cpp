#include "jEngine/Button.h"
#include "jEngine/System.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


namespace jengine{
    Button::Button(int x, int y, int w, int h, std::string txt): EventSprite(x, y, w, h)
    {
        //textTexture
        SDL_Surface* textSurface = TTF_RenderText_Solid(sys.getFont(), txt.c_str(), {0, 0, 0});
        textTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), textSurface);
        SDL_FreeSurface(textSurface);

        //buttonTextures
        buttonUpTexture = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/button/upButtonTx.png").c_str());
        buttonDownTexture = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/button/downButtonTx.png").c_str());
    }

    Button* Button::getInstance(int x, int y, int w, int h, std::string txt){
        return new Button(x, y, w, h, txt);
    }

    void Button::mouseDown(const SDL_Event& event){
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &getRect())){
            isDown = true;
        }
    }

    void Button::mouseUp(const SDL_Event& event){
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &getRect())){
            perform(this);
        }
    
        isDown = false;
    }

    std::string Button::getText() const{
        return text;
    }
    
    void Button::setText(std::string newText){
        text = newText;

        SDL_DestroyTexture(textTexture);

        //textTexture
        SDL_Surface* textSurface = TTF_RenderText_Solid(sys.getFont(), newText.c_str(), {0, 0, 0});
        textTexture = SDL_CreateTextureFromSurface(sys.getRenderer(), textSurface);
        SDL_FreeSurface(textSurface);
    }

    void Button::draw() const{
        if (isDown){
            SDL_RenderCopy(sys.getRenderer(), buttonDownTexture, nullptr, &getRect());
        }else{
            SDL_RenderCopy(sys.getRenderer(), buttonUpTexture, nullptr, &getRect());
        }
        SDL_RenderCopy(sys.getRenderer(), textTexture, nullptr, &getRect());
    }

    void Button::tick(){

    }
    Button::~Button()
    {
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(buttonUpTexture);
        SDL_DestroyTexture(buttonDownTexture);
    }
}
