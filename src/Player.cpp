#include <SDL2/SDL_events.h>
#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include <iostream>

namespace jengine {

    Player *Player::getInstance(int x, int y, int w, int h) {
        return new Player(x, y, w, h);
    }

    Player::Player(int x, int y, int w, int h) : EventSprite(x, y, w, h) {

        airTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/air.png").c_str());
        leftTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/left.png").c_str());
        rightTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/right.png").c_str());
        downTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/down.png").c_str());
        idelTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/idle.png").c_str());

        currentTx = idelTx;

        xDirection = 0;
        //yStart = h;
    }

    void Player::setXCollision(bool collision) {
        xCollision = collision;
    }

    void Player::setYCollision(bool collision) {
        yCollision = collision;
    }

    void Player::resetYVelocity() {
        yDirection = 0;
    }

    void Player::changeYVelocity(int y) {
        yDirection += y;
    }

    void Player::changeXVelocity(int x) {
        xDirection -= x;
    }

    int Player::getXVelocity() {
        return xDirection;
    }

    int Player::getYVelocity() {
        return yDirection;
    }

    int Player::getXPosition() {
        return rect.x;
    }

    int Player::getYPosition() {
        return rect.y;
    }

    void Player::setXPosition(int x) {
        rect.x = x;

    }

    void Player::setYPosition(int y) {
        rect.y = y;
    }

    void Player::keyDown(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:

                currentTx = downTx;

                break;
            case SDLK_LEFT:
                rect.x -= 30;
                currentTx = leftTx;

                break;
            case SDLK_RIGHT:
                rect.x += 30;
                currentTx = rightTx;
                break;
        }
    }

    void Player::keyUp(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                if (yCollision) {
                    setYPosition(rect.y - 15);
                    changeYVelocity(-20);
                }
                break;
            case SDLK_LEFT:
                currentTx = idelTx;
                break;
            case SDLK_RIGHT:
                currentTx = idelTx;
                break;
        }
    }

    void Player::draw() const {

        SDL_RenderCopy(sys.getRenderer(), currentTx, nullptr, &rect);

    }

    void Player::tick() {

        if (yDirection != 0) {
            currentTx = airTx;
        } else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idelTx;
        }

        rect.y += yDirection;
    }


    Player::~Player() {
        SDL_DestroyTexture(airTx);
        SDL_DestroyTexture(leftTx);
        SDL_DestroyTexture(rightTx);
        SDL_DestroyTexture(downTx);
        SDL_DestroyTexture(idelTx);
    }

} // jengine