#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h> 

namespace jengine{
    
class Sprite
{
public:
    //virtual destruktor för att säkerhetställa att destruktorer hos subklasser också kommer att anropas.
    virtual ~Sprite();

    virtual void draw() const = 0;

    virtual void tick() = 0;

    //behöver inte returnera en kopia av recten.
    const SDL_Rect& getRect() const {return rect;}

protected:
    Sprite(int x, int y, int w, int h);
    SDL_Rect rect;

private:

    //vid tilldelning och kopiering kan vi få slicing. (objekt som är olika stora tilldelas varandra)
    //förbjud kopiering
    Sprite(const Sprite&) = delete;
    //förbjud tilldelning
    const Sprite& operator=(const Sprite&) = delete;

};
}


#endif