#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
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

        void draw() const;

        void tick();

        ~Player();

    protected:
        Player(int x, int y, int w, int h);
    private:

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

        int yDirection;
        int xDirection;
        int yStart;

        bool yCollision;
        bool xCollision;

    };

} // jengine

#endif //PLAYER_H
