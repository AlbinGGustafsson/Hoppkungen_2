#include <SDL2/SDL_events.h>
#include "../include/Player.h"
#include <SDL2/SDL_image.h>
#include "../include/Constants.h"
#include "../include/System.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace constants;

namespace jengine {

    Player::Player(int x, int y, int w, int h) : EventSprite(x, y, w, h) {
        xVelocity = 0;
        yVelocity = 1;
        yCollision = false;
        xCollision = false;
    }

    void Player::setXCollision(bool collision) {
        xCollision = collision;
    }

    void Player::setYCollision(bool collision) {
        yCollision = collision;
    }

    void Player::resetYVelocity() {
        yVelocity = 0;
    }

    void Player::resetXVelocity(){
        xVelocity = 0;
    }

    void Player::changeYVelocity(int y) {
        yVelocity += y;
    }

    void Player::changeXVelocity(int x) {
        xVelocity += x;
    }

    int Player::getXVelocity() {
        return xVelocity;
    }

    int Player::getYVelocity() {
        return yVelocity;
    }

    void Player::setXPosition(int x) {
        rect.x = x;

    }

    void Player::setYPosition(int y) {
        rect.y = y;
    }

    void Player::setYVelocity(int y){
        yVelocity = y;
    }
    void Player::setXVelocity(int x){
        xVelocity = x;
    }

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

//    void Player::draw() const {
//        SDL_RenderCopy(sys.getRenderer(), currentTx, nullptr, &rect);
//    }

    void Player::tick() {

        if (yVelocity != 0) {
            rect.x += xVelocity;
        }
        rect.y += yVelocity;
    }


    void Player::spaceDown() {}

    void Player::spaceUp() {

        if (yVelocity == 0){
            setYPosition(rect.y - PLAYER_DOWNWARD_VELOCITY_GROWTH);
            changeYVelocity(-JUMP_VELOCITY);
        }
    }

    void Player::leftDown() {

        if (!xCollision){
            rect.x -= HORIZONTAL_MOVEMENT;
        }
    }

    void Player::rightDown() {

        if (!xCollision){
            rect.x += HORIZONTAL_MOVEMENT;

        }
    }


    void Player::leftUp() {}

    void Player::rightUp() {}

    void Player::changePlayerSFXVolume(int volume) {
        Mix_Volume(JUMP_CHARGE_CHANNEL, volume);
        Mix_Volume(JUMP_CHANNEL, volume);
        Mix_Volume(WALKING_CHANNEL, volume);
    }

    Player::~Player() {

    }

} // jengine