#ifndef PLAYER_H
#define PLAYER_H
#include "EventSprite.h"
namespace jengine {

    class Player:public EventSprite{
    public:

        void keyDown(const SDL_Event &event) override;
        void keyUp(const SDL_Event &event) override;
        void tick() override;
        void gravity() override;
        ~Player();

    protected:
        Player(int x, int y, int w, int h);

        virtual void spaceDown();
        virtual void spaceUp();
        virtual void leftDown();
        virtual void rightDown();
        virtual void leftUp();
        virtual void rightUp();
        virtual void upDown();
        virtual void downDown();
        virtual void upUp();
        virtual void downUp();

    private:



    };

} // jengine

#endif //PLAYER_H
