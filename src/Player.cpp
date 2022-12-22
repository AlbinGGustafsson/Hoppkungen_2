#include <SDL2/SDL_events.h>
#include "Player.h"


using namespace constants;

namespace jengine {

    Player::Player(int x, int y, int w, int h) : EventSprite(x, y, w, h) {}


    void Player::keyDown(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                spaceDown();
                break;
            case SDLK_LEFT:
                leftDown();
                break;
            case SDLK_RIGHT:
                rightDown();
                break;
        }
    }

    void Player::keyUp(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                spaceUp();
                break;
            case SDLK_LEFT:
                leftUp();
                break;
            case SDLK_RIGHT:
                rightUp();
                break;
        }
    }

    void Player::tick() {

        if (getYVelocity() != 0) {
            setXPosition(getXPosition() + getXVelocity());
        }
        setYPosition(getYPosition() + getYVelocity());
    }

    void Player::gravity() {
        if (getYVelocity() < MAX_PLAYER_DOWNWARD_VELOCITY) {
            changeYVelocity(PLAYER_DOWNWARD_VELOCITY_GROWTH);
        }
        setYCollision(false);
        setXCollision(false);
    }

    void Player::spaceDown() {}

    void Player::spaceUp() {

        if (getYVelocity() == 0){
            setYPosition(getRect().y - PLAYER_DOWNWARD_VELOCITY_GROWTH);
            changeYVelocity(-JUMP_VELOCITY);
        }
    }

    void Player::leftDown() {

        if (!getXCollision()){
            setXPosition(getXPosition() - HORIZONTAL_MOVEMENT);
        }
    }

    void Player::rightDown() {

        if (!getXCollision()){
            setXPosition(getXPosition() + HORIZONTAL_MOVEMENT);
        }
    }


    void Player::leftUp() {}

    void Player::rightUp() {}


    Player::~Player() {

    }

} // jengine