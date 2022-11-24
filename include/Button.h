#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <EventSprite.h>

namespace jengine{
class Button : public EventSprite
{
public:
    static Button* getInstance(int x, int y, int w, int h, std::string txt);

    void mouseDown(const SDL_Event& event);
    void mouseUp(const SDL_Event& event);
    void draw() const;
    void tick();

    //lek
    std::string getText() const;
    void setText(std::string newText);
    //lek

    virtual void perform(Button* source) {};

    ~Button();

protected:
    Button(int x, int y, int w, int h, std::string txt);

private:
    std::string text;
    SDL_Texture* textTexture;
    SDL_Texture* buttonUpTexture;
    SDL_Texture* buttonDownTexture;

    bool isDown = false;
};
}


#endif