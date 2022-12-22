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

    void mouseDown(const SDL_Event& event) override;
    void mouseUp(const SDL_Event& event) override;
    void draw() const override;
    void tick() override;

    std::string getText() const;
    void setText(std::string newText);

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