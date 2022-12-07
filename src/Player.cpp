#include <SDL2/SDL_events.h>
#include "../include/Player.h"
#include <SDL2/SDL_image.h>
#include "../include/Constants.h"
#include "../include/System.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

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

        if (yVelocity != 0) {
            rect.x += xVelocity;
        }
        rect.y += yVelocity;
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

        if (yVelocity == 0){
            setYPosition(rect.y - PLAYER_DOWNWARD_VELOCITY_GROWTH);
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