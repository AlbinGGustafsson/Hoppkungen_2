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

        xVelocity = 0;
        yVelocity = 1;

        chargeJump = false;
        verticalCounter = 0;
        heightCounter = 0;

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

    void Player::setYVelocity(int y){
        yVelocity = y;
    }
    void Player::setXVelocity(int x){
        xVelocity = x;
    }

    void Player::keyDown(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:

                if (yCollision) {
                    if (!chargeJump){
                        chargeJump = true;
                        std::cout << "charging jump" << std::endl;
                        heightCounter+=10;
                    }

                    if (heightCounter < 25){
                        heightCounter+=0.5;
                        std::cout << "hc: "  << heightCounter << std::endl;
                    }else{
                        std::cout << "max horizontal charge charge" << std::endl;
                    }

                    currentTx = downTx;
                }

                break;
            case SDLK_LEFT:

                if (!chargeJump && yVelocity == 0 && !xCollision){
                    rect.x -= 20;
                    currentTx = leftTx;
                }

                if (chargeJump){
                    if (verticalCounter == 0){
                        verticalCounter-=2;
                        std::cout << "vc: " << verticalCounter <<  std::endl;
                    }else if (verticalCounter < 10 && verticalCounter > -10){
                        verticalCounter-=0.5;
                        std::cout << "vc: " << verticalCounter <<  std::endl;
                    }else{
                        std::cout << "max vertical charge" << std::endl;
                    }

                }
                break;
            case SDLK_RIGHT:

                if (!chargeJump && yVelocity == 0 && !xCollision){
                    rect.x += 20;
                    currentTx = rightTx;
                }

                if (chargeJump){

                    if (verticalCounter == 0){
                        verticalCounter+=2;
                        std::cout << "vc: " << verticalCounter <<  std::endl;
                    }else if (verticalCounter < 10 && verticalCounter > -10){
                        verticalCounter+=0.5;
                        std::cout << "vc: " << verticalCounter <<  std::endl;
                    }else{
                        std::cout << "max vertical charge" << std::endl;
                    }

                }
                break;
        }
    }

    void Player::keyUp(const SDL_Event &event) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                if (yCollision) {
                    //man klippar bara 1 pixel nu detta kanske bör ändras
                    setYPosition(rect.y - 15);
                    changeYVelocity(static_cast<int>(-heightCounter));

                    chargeJump = false;

                    changeXVelocity(static_cast<int>(verticalCounter));
                    verticalCounter = 0;
                    heightCounter = 0;

                }
                break;
            case SDLK_LEFT:

                if (!chargeJump){
                    currentTx = idelTx;
                }

                break;
            case SDLK_RIGHT:

                if (!chargeJump){
                    currentTx = idelTx;
                }

                break;
        }
    }

    void Player::draw() const {

        SDL_RenderCopy(sys.getRenderer(), currentTx, nullptr, &rect);

    }

    void Player::tick() {

        if (yVelocity != 0) {
            currentTx = airTx;

            //Resettar en charge när man faller/åker upp.
            chargeJump = false;
            verticalCounter = 0;
            heightCounter = 0;
            //

            rect.x += xVelocity;

        } else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idelTx;
        }

        rect.y += yVelocity;
    }


    Player::~Player() {
        SDL_DestroyTexture(airTx);
        SDL_DestroyTexture(leftTx);
        SDL_DestroyTexture(rightTx);
        SDL_DestroyTexture(downTx);
        SDL_DestroyTexture(idelTx);
    }

} // jengine