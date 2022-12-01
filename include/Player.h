#ifndef PLAYER_H
#define PLAYER_H
#include "EventSprite.h"
namespace jengine {

    class Player:public EventSprite{
    public:
        void setXCollision(bool collision);
        void setYCollision(bool collision);

        void setXPosition(int x);
        void setYPosition(int y);

        int getXVelocity();
        int getYVelocity();

        void keyDown(const SDL_Event &event);
        void keyUp(const SDL_Event &event);
        void tick();

        void resetYVelocity();
        void resetXVelocity();

        void changeYVelocity(int y);
        void changeXVelocity(int x);

        void setYVelocity(int y);
        void setXVelocity(int x);

        void changePlayerSFXVolume(int volume);

        virtual void spaceDown();
        virtual void spaceUp();
        virtual void leftDown();
        virtual void rightDown();
        virtual void leftUp();
        virtual void rightUp();


        ~Player();

    protected:
        Player(int x, int y, int w, int h);

        int yVelocity;
        int xVelocity;

        bool yCollision;
        bool xCollision;


    private:

    };

} // jengine

#endif //PLAYER_H
