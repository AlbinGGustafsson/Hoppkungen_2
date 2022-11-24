#include "Label.h"
#include "System.h"
#include <SDL2/SDL_ttf.h>

namespace jengine{



Label* Label::getInstance(int x, int y, int w, int h, std::string txt){
    return new Label(x, y, w, h, txt);
}


Label::Label(int x, int y, int w, int h, std::string txt): NonEventSprite(x, y, w, h), text(txt)
{
    SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
    SDL_FreeSurface(surface);
}

void Label::draw() const {
    //första NULL = ta hela texturen
    //sista så vill den ha en pekare till en rect (adressen till en pekare)
    SDL_RenderCopy(sys.getRenderer(), texture, nullptr, &getRect());
}

void Label::tick(){

}

std::string Label::getText() const{
    return text;
}
    
void Label::setText(std::string newText){
    text = newText;

    SDL_DestroyTexture(texture);
    SDL_Surface* surface = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(sys.getRenderer(), surface);
    SDL_FreeSurface(surface);
}

Label::~Label()
{
    SDL_DestroyTexture(texture);
}

}
