#include "Game/Hoppkung.h"
#include "Constants.h"
#include <iostream>

using namespace std;
using namespace constants;
using namespace jengine;

HoppKung::HoppKung(int x, int y, int w, int h, std::vector<std::vector<Sprite *>>& lvls, GameEngine& session) : Amongus(x, y, w, h), levels(lvls), ses(session), chargingJump(false), horizontalCounter(0),
                                                                                                                verticalCounter(0){}


void HoppKung::spaceDown() {
    //Börjar ladda ett hopp om man står på en platform.
    if (getYCollision()) {
        if (!chargingJump) {
            chargingJump = true;
            std::cout << "charging jump" << std::endl;
            verticalCounter += INITIAL_VERTICAL_CHARGE_VELOCITY;

            Mix_PlayChannel(JUMP_CHARGE_CHANNEL, getJumpChargeSfx(), 0);
        }

        //Om man fortsätter hålla in space ökar laddningen av hoppet.
        if (verticalCounter < MAX_PLAYER_VERTICAL_CHARGE_VELOCITY) {
            verticalCounter += PLAYER_VERTICAL_CHARGE_GROWTH;
            std::cout << "hc: " << verticalCounter << std::endl;
        } else {
            std::cout << "max vertical charge charge" << std::endl;
        }

        setCurrentTx(getDownTx());

    }
}

void HoppKung::spaceUp() {
    //Om man är på en platform.
    //Utlöser hoppet, sätter x och y hastigheten till det som kalkylerats i space, left, right down.
    if (getYCollision()) {
        setYPosition(getRect().y - INITIAL_JUMP_MOVEMENT);
        changeYVelocity(static_cast<int>(-verticalCounter));

        chargingJump = false;

        changeXVelocity(static_cast<int>(horizontalCounter));
        horizontalCounter = 0;
        verticalCounter = 0;

        Mix_HaltChannel(JUMP_CHARGE_CHANNEL);
        Mix_PlayChannel(JUMP_CHANNEL, getJumpSfx(), 0);
    }
}

void HoppKung::leftDown() {
    //Spelaren går till vänster, sätter texture och spelar ljudeffekt om man inte är i luften och inte laddar ett hopp och inte har en kollision med en vägg.
    if (!chargingJump && getYVelocity() == 0 && !getXCollision()) {
        setXPosition(getXPosition() - HORIZONTAL_MOVEMENT);
        setCurrentTx(getLeftTx());
        if (Mix_Playing(WALKING_CHANNEL) == 0) {
            Mix_PlayChannel(WALKING_CHANNEL, getWalkingSfx(), 0);
        }
    }

    //Logik för att kalkylera hur långt vänster ett hopp ska ske
    if (chargingJump) {
        if (horizontalCounter == 0) {
            horizontalCounter -= INITIAL_HORIZONTAL_CHARGE_VELOCITY;
            std::cout << "vc: " << horizontalCounter << std::endl;
        } else if (horizontalCounter < MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY &&
                   horizontalCounter > -MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY) {
            horizontalCounter -= PLAYER_HORIZONTAL_CHARGE_GROWTH;
            std::cout << "vc: " << horizontalCounter << std::endl;
        } else {
            std::cout << "max horizontal charge" << std::endl;
        }

    }
}

void HoppKung::rightDown() {
    //Spelaren går till höger, sätter texture och spelar ljudeffekt om man inte är i luften och inte laddar ett hopp och inte har en kollision med en vägg.
    if (!chargingJump && getYVelocity() == 0 && !getXCollision()) {
        setXPosition(getXPosition() + HORIZONTAL_MOVEMENT);
        setCurrentTx(getRightTx());
        if (Mix_Playing(WALKING_CHANNEL) == 0) {
            Mix_PlayChannel(WALKING_CHANNEL, getWalkingSfx(), 0);
        }
    }


    //Logik för att kalkylera hur långt höger ett hopp ska ske
    if (chargingJump) {
        if (horizontalCounter == 0) {
            horizontalCounter += INITIAL_HORIZONTAL_CHARGE_VELOCITY;
            std::cout << "vc: " << horizontalCounter << std::endl;
        } else if (horizontalCounter < MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY &&
                   horizontalCounter > -MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY) {
            horizontalCounter += PLAYER_HORIZONTAL_CHARGE_GROWTH;
            std::cout << "vc: " << horizontalCounter << std::endl;
        } else {
            std::cout << "max horizontal charge" << std::endl;
        }
    }
}

void HoppKung::leftUp() {
    if (!chargingJump) {
        setCurrentTx(getIdleTx());
    }
}

void jengine::HoppKung::rightUp() {
    if (!chargingJump) {
        setCurrentTx(getIdleTx());
    }
}

void HoppKung::tick() {

    //Byter level när spelaren flyttar upp ovanför fönstret
    if (getYPosition() < 0) {
        if ((currentLevel + 1) < static_cast<int>(levels.size())) {
            ses.setLevel(levels[currentLevel + 1]);
            currentLevel++;
            setYPosition(WINDOW_HEIGHT);
        }
    }

    //Byter level när spelaren flyttar ned under fönstret
    if (getYPosition() > WINDOW_HEIGHT) {
        if (currentLevel - 1 >= 0) {
            ses.setLevel(levels[currentLevel - 1]);
            currentLevel--;
            setYPosition(0);
        }

    }

    //spelaren flyttar till andra sidan när den går utanför till höger
    if (getXPosition() + getRect().w > WINDOW_WIDTH + getRect().w / 2) {
        setXPosition(-getRect().w / 2);
    }

    //spelaren flyttar till andra sidan när den går utanför till vänster
    if (getXPosition() < -getRect().w / 2) {
        setXPosition(WINDOW_WIDTH + getRect().w / 2 - getRect().w);
    }

    //När man är i luften så sätter den spelarens texture till air och ett hopp återställs.
    if (getYVelocity() != 0) {
        setCurrentTx(getAirTx());


        Mix_HaltChannel(JUMP_CHARGE_CHANNEL);
        chargingJump = false;
        horizontalCounter = 0;
        verticalCounter = 0;

        setXPosition(getXPosition() + getXVelocity());

        //Återställer texture till idle när man landar
    } else if (!(getCurrentTx() == getLeftTx() || getCurrentTx() == getRightTx() ||
                 getCurrentTx() == getDownTx())) {
        setCurrentTx(getIdleTx());
    }

    setYPosition(getYPosition() + getYVelocity());
}


