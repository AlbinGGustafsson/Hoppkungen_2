#ifndef AMONGUS_H
#define AMONGUS_H
#include "jEngine/Player.h"

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

        SDL_Texture *getAirTx() const;
        SDL_Texture *getLeftTx() const;
        SDL_Texture *getRightTx() const;
        SDL_Texture *getDownTx() const;
        SDL_Texture *getIdleTx() const;
        SDL_Texture *getCurrentTx() const;

        Mix_Chunk *getWalkingSfx() const;
        Mix_Chunk *getJumpChargeSfx() const;
        Mix_Chunk *getJumpSfx() const;

        void setAirTx(SDL_Texture *airTx);
        void setLeftTx(SDL_Texture *leftTx);
        void setRightTx(SDL_Texture *rightTx);
        void setDownTx(SDL_Texture *downTx);
        void setIdleTx(SDL_Texture *idleTx);
        void setCurrentTx(SDL_Texture *currentTx);

    protected:
        Amongus(int x, int y, int w, int h);
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
        SDL_Texture* idleTx;

        //current texture
        SDL_Texture* currentTx;


        //WalkingSound
        Mix_Chunk* walkingSFX;
        //jump charge sound
        Mix_Chunk* jumpChargeSFX;
        //jump sound
        Mix_Chunk* jumpSFX;
    };

}




#endif
