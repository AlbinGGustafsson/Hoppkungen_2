#ifndef LABEL_H
#define LABEL_H
#include "NonEventSprite.h"
#include <string>
#include <SDL2/SDL.h>

namespace jengine{
class Label: public NonEventSprite
{
public:
    static Label* getInstance(int x, int y, int w, int h, std::string txt);

    void draw() const;

    void tick();

    std::string getText() const;
    void setText(std::string newText);
    
    ~Label();

protected:
    Label(int x, int y, int w, int h, std::string txt);
    SDL_Texture* texture;

private:
    std::string text;

};
}

#endif