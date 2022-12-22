#include "Amongus.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_mixer.h>

namespace jengine{

using namespace constants;

    Amongus::Amongus(int x, int y, int w, int h) : Player(x, y, w, h) {

        airTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/air.png").c_str());
        leftTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/left.png").c_str());
        rightTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/right.png").c_str());
        downTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/down.png").c_str());
        idleTx = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/idle.png").c_str());
        walkingSFX = Mix_LoadWAV((constants::gResPath + "sounds/grassFootstep.mp3").c_str());
        jumpChargeSFX = Mix_LoadWAV((constants::gResPath + "sounds/charge.mp3").c_str());
        jumpSFX = Mix_LoadWAV((constants::gResPath + "sounds/jump.mp3").c_str());

        currentTx = idleTx;

    }

    Amongus::~Amongus() {

        Mix_FreeChunk(jumpChargeSFX);
        Mix_FreeChunk(jumpSFX);
        Mix_FreeChunk(walkingSFX);
        SDL_DestroyTexture(airTx);
        SDL_DestroyTexture(leftTx);
        SDL_DestroyTexture(rightTx);
        SDL_DestroyTexture(downTx);
        SDL_DestroyTexture(idleTx);

    }

    void Amongus::draw() const {
        SDL_RenderCopy(sys.getRenderer(), currentTx, nullptr, &getRect());
    }

    void Amongus::tick() {
        if (getYVelocity() != 0) {
            currentTx = airTx;
            setXPosition(getXPosition() + getXVelocity());

        }
        //Återställer till idle när man landar
        else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idleTx;
        }

        setYPosition(getYPosition() + getYVelocity());
    }

    void Amongus::spaceDown() {
        Player::spaceDown();
    }

    void Amongus::spaceUp() {
        if (getYVelocity() == 0){
            setYPosition(getRect().y - PLAYER_DOWNWARD_VELOCITY_GROWTH);
            changeYVelocity(-JUMP_VELOCITY);
            Mix_PlayChannel(JUMP_CHANNEL, jumpSFX, 0);
        }
    }

    void Amongus::leftDown() {
        if (!getXCollision()){
            setXPosition(getXPosition() - HORIZONTAL_MOVEMENT);

            currentTx = leftTx;

            if (getYVelocity() == 0 && Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }
    }

    void Amongus::rightDown() {
        if (!getXCollision()){
            setXPosition(getXPosition() + HORIZONTAL_MOVEMENT);
            currentTx = rightTx;

            if (getYVelocity() == 0 && Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }
    }

    void Amongus::leftUp() {
        currentTx = idleTx;
    }

    void Amongus::rightUp() {
        currentTx = idleTx;
    }

    Amongus *Amongus::getInstance(int x, int y, int w, int h) {
        return new Amongus(x, y, w, h);
    }

    SDL_Texture *Amongus::getAirTx() const {
        return airTx;
    }

    SDL_Texture *Amongus::getLeftTx() const {
        return leftTx;
    }

    SDL_Texture *Amongus::getRightTx() const {
        return rightTx;
    }

    SDL_Texture *Amongus::getDownTx() const {
        return downTx;
    }

    SDL_Texture *Amongus::getIdleTx() const {
        return idleTx;
    }

    SDL_Texture *Amongus::getCurrentTx() const {
        return currentTx;
    }

    Mix_Chunk *Amongus::getWalkingSfx() const {
        return walkingSFX;
    }

    Mix_Chunk *Amongus::getJumpChargeSfx() const {
        return jumpChargeSFX;
    }

    Mix_Chunk *Amongus::getJumpSfx() const {
        return jumpSFX;
    }

    void Amongus::setAirTx(SDL_Texture *airTx) {
        Amongus::airTx = airTx;
    }

    void Amongus::setLeftTx(SDL_Texture *leftTx) {
        Amongus::leftTx = leftTx;
    }

    void Amongus::setRightTx(SDL_Texture *rightTx) {
        Amongus::rightTx = rightTx;
    }

    void Amongus::setDownTx(SDL_Texture *downTx) {
        Amongus::downTx = downTx;
    }

    void Amongus::setIdleTx(SDL_Texture *idleTx) {
        Amongus::idleTx = idleTx;
    }

    void Amongus::setCurrentTx(SDL_Texture *currentTx) {
        Amongus::currentTx = currentTx;
    }
}