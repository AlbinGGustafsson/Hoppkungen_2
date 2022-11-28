#include "System.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace jengine{

System::System()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Jengine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1200, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();
    font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);

}

System::~System()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

SDL_Renderer* System::getRenderer() const{
    return renderer;
}

TTF_Font* System::getFont() const {
    return font;
}

//eftersom den ligger utanför funktioner så blir det ett statiskt objekt.
//Måste vara deklarerad som extern i headerfilen.
System sys;

}