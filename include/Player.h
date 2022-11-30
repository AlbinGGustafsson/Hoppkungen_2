#ifndef PLAYER_H
#define PLAYER_H
#include "EventSprite.h"
namespace jengine {

    class Player:public EventSprite{
    public:
        static Player* getInstance(int x, int y, int w, int h);

        void setXCollision(bool collision);
        void setYCollision(bool collision);

        void setXPosition(int x);
        void setYPosition(int y);

        int getXPosition();
        int getYPosition();

        int getXVelocity();
        int getYVelocity();

        void keyDown(const SDL_Event &event);

        void keyUp(const SDL_Event &event);

        void resetYVelocity();
        void resetXVelocity();

        void changeYVelocity(int y);
        void changeXVelocity(int x);

        void setYVelocity(int y);
        void setXVelocity(int x);

        void changePlayerSFXVolume(int volume);


        void draw() const;

        void tick();


        virtual void spaceDown();
        virtual void spaceUp();
        virtual void leftDown();
        virtual void rightDown();
        virtual void leftUp();
        virtual void rightUp();


        ~Player();

    protected:
        Player(int x, int y, int w, int h);


        //InAirImage
        SDL_Texture* airTx;
        //WalkLeftImage
        SDL_Texture* leftTx;
        //WalkRightImage
        SDL_Texture* rightTx;
        //SpaceDownImage
        SDL_Texture* downTx;
        //StandingImage
        SDL_Texture* idleTx;

        //current texture
        SDL_Texture* currentTx;


        //WalkingSound
        Mix_Chunk* walkingSFX;
        //jump charge sound
        Mix_Chunk* jumpChargeSFX;
        //jump sound
        Mix_Chunk* jumpSFX;

        int yVelocity;
        int xVelocity;

        bool yCollision;
        bool xCollision;

    private:

    };

} // jengine

#endif //PLAYER_H
