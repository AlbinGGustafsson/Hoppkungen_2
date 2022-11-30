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

        void setFootstepSoundFX(std::string soundFileName);

        void draw() const;

        void tick();

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
        SDL_Texture* idelTx;

        //current texture
        SDL_Texture* currentTx;


        //WalkingSound
        Mix_Chunk* walkingSFX;
        //jump charge sound
        Mix_Chunk* jumpCharge;

        //jump sound
        Mix_Chunk* jump;

        int yVelocity;
        int xVelocity;

        bool yCollision;
        bool xCollision;

        bool chargeJump;
        double verticalCounter;
        double heightCounter;
        bool jumpChargePlaying;

    private:


    };

} // jengine

#endif //PLAYER_H
