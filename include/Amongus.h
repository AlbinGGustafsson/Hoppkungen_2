#ifndef AMONGUS_H
#define AMONGUS_H
#include "Player.h"

namespace jengine{

    class Amongus:public Player{

    public:
        static Amongus* getInstance(int x, int y, int w, int h);

        ~Amongus();

        void draw() const override;

        void tick() override;

        void spaceDown() override;

        void spaceUp() override;

        void leftDown() override;

        void rightDown() override;

        void leftUp() override;

        void rightUp() override;

    protected:
        Amongus(int x, int y, int w, int h);


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

    private:


    };

}




#endif
