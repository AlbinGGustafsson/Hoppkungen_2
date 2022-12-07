#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Constants.h"

namespace jengine{
    
class Sprite
{
public:
    //virtual destruktor för att säkerhetställa att destruktorer hos subklasser också kommer att anropas.
    virtual ~Sprite();

    virtual void draw() const = 0;
    virtual void tick() = 0;
    virtual void collision(Sprite* other) {}
    virtual void gravity() {}

    const SDL_Rect& getRect() const {return rect;}
    void checkCollision(Sprite* other);

    int getXPosition() const;
    int getYPosition() const;

    void setXPosition(int x);
    void setYPosition(int y);

    void setXCollision(bool collision);
    void setYCollision(bool collision);

    bool getXCollision() const;
    bool getYCollision() const;

    int getXVelocity() const;
    int getYVelocity() const;

    void resetYVelocity();
    void resetXVelocity();

    void changeYVelocity(int y);
    void changeXVelocity(int x);

    void setYVelocity(int y);
    void setXVelocity(int x);

protected:
    Sprite(int x, int y, int w, int h);

private:
    //vid tilldelning och kopiering kan vi få slicing. (objekt som är olika stora tilldelas varandra)
    //förbjud kopiering
    Sprite(const Sprite&) = delete;
    //förbjud tilldelning
    const Sprite& operator=(const Sprite&) = delete;

    int yVelocity;
    int xVelocity;

    bool yCollision;
    bool xCollision;

    SDL_Rect rect;

};
}


#endif