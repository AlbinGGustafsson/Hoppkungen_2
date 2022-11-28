#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>


namespace jengine {
class System {
public:
    System();
    ~System();
    SDL_Renderer* getRenderer() const;
    TTF_Font* getFont() const;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font* font;

};

//Alla som inkluderar denna headerfil får en deklaration att det finns någon stans ett objekt som heter sys av typen System. (Objektet finns i system.cpp)
extern System sys;
//har man inte det så kommer objektet sys vara deklarerad på flera ställen. (Överallt där system.h inkluderas)

} // namespace cwing

#endif