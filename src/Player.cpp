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
        idleTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/idle.png").c_str());
        walkingSFX = Mix_LoadWAV((constants::gResPath + "sounds/grassFootstep.mp3").c_str());
        jumpChargeSFX = Mix_LoadWAV((constants::gResPath + "sounds/charge.mp3").c_str());
        jumpSFX = Mix_LoadWAV((constants::gResPath + "sounds/jump.mp3").c_str());

        currentTx = idleTx;

        xVelocity = 0;
        yVelocity = 1;

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

    void Player::draw() const {

        SDL_RenderCopy(sys.getRenderer(), currentTx, nullptr, &rect);

    }

    void Player::tick() {

        if (yVelocity != 0) {
            currentTx = airTx;
            rect.x += xVelocity;

        }
        //Återställer till idle när man landar
        else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idleTx;
        }

        rect.y += yVelocity;
    }


    Player::~Player() {
        Mix_FreeChunk(jumpChargeSFX);
        Mix_FreeChunk(jumpSFX);
        Mix_FreeChunk(walkingSFX);
        SDL_DestroyTexture(airTx);
        SDL_DestroyTexture(leftTx);
        SDL_DestroyTexture(rightTx);
        SDL_DestroyTexture(downTx);
        SDL_DestroyTexture(idleTx);
    }

    void Player::spaceDown() {
        if (yVelocity == 0){
            currentTx = downTx;
        }
    }

    void Player::spaceUp() {

        if (yVelocity == 0){
            setYPosition(rect.y - PLAYER_DOWNWARD_VELOCITY_GROWTH);
            changeYVelocity(-JUMP_VELOCITY);
            Mix_PlayChannel(JUMP_CHANNEL, jumpSFX, 0);
        }
    }

    void Player::leftDown() {

        if (!xCollision){
            rect.x -= HORIZONTAL_MOVEMENT;
            currentTx = leftTx;

            if (yVelocity == 0 && Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }
    }

    void Player::rightDown() {

        if (!xCollision){
            rect.x += HORIZONTAL_MOVEMENT;
            currentTx = rightTx;

            if (yVelocity == 0 && Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }
    }


    void Player::leftUp() {
        currentTx = idleTx;
    }

    void Player::rightUp() {
        currentTx = idleTx;
    }

    void Player::changePlayerSFXVolume(int volume) {
        Mix_Volume(JUMP_CHARGE_CHANNEL, volume);
        Mix_Volume(JUMP_CHANNEL, volume);
        Mix_Volume(WALKING_CHANNEL, volume);
    }

} // jengine