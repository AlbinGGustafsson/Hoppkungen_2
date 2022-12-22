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

    void draw() const override;

    void tick() override;

    std::string getText() const;
    void setText(std::string newText);

    SDL_Texture *getTexture() const;

    void setTexture(SDL_Texture *texture);

    ~Label();

protected:
    Label(int x, int y, int w, int h, std::string txt);

private:
    std::string text;
    SDL_Texture* texture;
};
}

#endif