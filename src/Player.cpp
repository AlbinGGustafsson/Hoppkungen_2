#include <SDL2/SDL_events.h>
#include "../include/Player.h"
#include <SDL2/SDL_image.h>
#include "../include/Constants.h"
#include "../include/System.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

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
        walkingSFX = Mix_LoadWAV((constants::gResPath + "sounds/grassFootstep.mp3").c_str());
        jumpCharge = Mix_LoadWAV((constants::gResPath + "sounds/charge.mp3").c_str());
        jump = Mix_LoadWAV((constants::gResPath + "sounds/jump.mp3").c_str());

        currentTx = idelTx;

        xVelocity = 0;
        yVelocity = 1;

        jumpChargePlaying = false;
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

    void Player::setFootstepSoundFX(std::string fileName) {
        walkingSFX = Mix_LoadWAV((constants::gResPath + "sounds/" + fileName).c_str());
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
                    if(!jumpChargePlaying){
                        Mix_PlayChannel(0, jumpCharge, 0);
                        jumpChargePlaying = true;
                    }

                }

                break;
            case SDLK_LEFT:

                if (!chargeJump && yVelocity == 0 && !xCollision){
                    rect.x -= 20;
                    currentTx = leftTx;
                    Mix_PlayChannel(2, walkingSFX, 0);
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
                    Mix_PlayChannel(2, walkingSFX, 0);
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
                    jumpChargePlaying = false;

                    changeXVelocity(static_cast<int>(verticalCounter));
                    verticalCounter = 0;
                    heightCounter = 0;

                }

                Mix_PlayChannel(0, jump, 0);
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
        Mix_FreeChunk(walkingSFX);
        SDL_DestroyTexture(airTx);
        SDL_DestroyTexture(leftTx);
        SDL_DestroyTexture(rightTx);
        SDL_DestroyTexture(downTx);
        SDL_DestroyTexture(idelTx);
    }

} // jengine