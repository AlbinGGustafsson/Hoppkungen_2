#include <SDL2/SDL.h>
#include "jEngine/Label.h"
#include "jEngine/GameEngine.h"
#include <string>
#include "jEngine/Player.h"
#include "Game/StoneTerrain.h"
#include "jEngine/Background.h"
#include "Game/Amongus.h"

#include <iostream>

using namespace jengine;
using namespace std;
using namespace constants;

GameEngine ses;
std::vector<std::vector<Sprite *>> levels;

class MovingStoneTerrain : public StoneTerrain {
public:

    static MovingStoneTerrain* getInstance(int x, int y, int w, int h){
        return new MovingStoneTerrain(x, y, w, h);
    }

    void collision(Sprite *other) override {
        Terrain::collision(other);

        if (dynamic_cast<Terrain *>(other)) {
            cout << "krock" << endl;
        }
    }

    void aboveCollision(Player *p) override {
        p->setYCollision(true);
        p->setYPosition(getRect().y + 10 - p->getRect().h);
        p->setYVelocity(-p->getYVelocity());
    }

    void tick() {
        if (moveRight) {
            if (getRect().x < 995) {
                setXPosition(getXPosition() + 3);
            }

            if (getRect().x > 995) {
                moveRight = false;
            }
        }

        if (!moveRight) {

            if (getRect().x > 5) {
                setXPosition(getXPosition() - 3);
            }
            if (getRect().x < 5) {
                moveRight = true;
            }

        }
    }

protected:
    MovingStoneTerrain(int x, int y, int w, int h) : StoneTerrain(x, y, w, h) {}
private:

    bool moveRight = true;
};

class HoppKungen : public Amongus {
public:

    static HoppKungen* getInstance(int x, int y, int w, int h) {
        return new HoppKungen(x, y, w, h);
    }

    void spaceDown() override {

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

    void spaceUp() override {

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

    void leftDown() override {

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

    void rightDown() override {

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

    void leftUp() override {
        if (!chargingJump) {
            setCurrentTx(getIdleTx());
        }
    }

    void rightUp() override {
        if (!chargingJump) {
            setCurrentTx(getIdleTx());
        }
    }


    void tick() override {

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

    int getCurrentLevel() const {
        return currentLevel;
    }

protected:
    HoppKungen(int x, int y, int w, int h) : Amongus(x, y, w, h), chargingJump(false), horizontalCounter(0), verticalCounter(0) {}

private:
    static const int MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY = 10;
    static const int INITIAL_HORIZONTAL_CHARGE_VELOCITY = 2;
    static const int INITIAL_VERTICAL_CHARGE_VELOCITY = 10;
    static const int INITIAL_JUMP_MOVEMENT = 15;
    static const int MAX_PLAYER_VERTICAL_CHARGE_VELOCITY = 25;
    constexpr static const double PLAYER_HORIZONTAL_CHARGE_GROWTH = 0.5;
    constexpr static const double PLAYER_VERTICAL_CHARGE_GROWTH = 0.5;
    static const int HORIZONTAL_MOVEMENT = 20;

    int currentLevel = 0;
    bool chargingJump;
    double horizontalCounter;
    double verticalCounter;

};


class HeightLabel : public Label {
public:

    static HeightLabel* getInstance(int x, int y, int w, int h, HoppKungen* p){
        return new HeightLabel(x, y, w, h, p);
    }

    void tick() {

        int height = player->getCurrentLevel() * WINDOW_HEIGHT + (1200 - player->getYPosition());
        setText(to_string(height));
    }

protected:
    HeightLabel(int x, int y, int w, int h, HoppKungen *p) : Label(x, y, w, h, ""), player(p) {}

private:
    HoppKungen *player;

};


int main(int argc, char **argv) {

    std::vector<Sprite *> level1;
    std::vector<Sprite *> level2;
    std::vector<Sprite *> level3;

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);


    Background *bg = Background::getInstance(0, 0, 0, 0, "bg1.png", "bgMusic1.mp3", 10);
    Background *bg2 = Background::getInstance(0, 0, 0, 0, "bg2.png", "bgMusic2.mp3", 128);

    HoppKungen *player = HoppKungen::getInstance(600, 110, 100, 100);
    ses.changeSFXVolume(30);


    //StoneTerrain *t0 = StoneTerrain::getInstance(-100, 1150, 1400, 50);
    StoneTerrain *t1 = StoneTerrain::getInstance(380, 900, 200, 50);
    StoneTerrain *t2 = StoneTerrain::getInstance(600, 700, 200, 50);
    StoneTerrain *t3 = StoneTerrain::getInstance(900, 450, 200, 50);
    StoneTerrain *t4 = StoneTerrain::getInstance(600, 220, 200, 50);
    StoneTerrain *t5 = StoneTerrain::getInstance(100, 380, 200, 50);

    HeightLabel *heightLabel = HeightLabel::getInstance(50,50,50,30, player);
    StoneTerrain *t6 = MovingStoneTerrain::getInstance(900, 800, 200, 50);

    StoneTerrain *t7 = StoneTerrain::getInstance(-100, 950, 320, 70);
    StoneTerrain *t8 = StoneTerrain::getInstance(150, 950, 320, 70);
    StoneTerrain *t9 = StoneTerrain::getInstance(400, 950, 320, 70);
    StoneTerrain *t10 = StoneTerrain::getInstance(650, 950, 320, 70);
    StoneTerrain *t100 = StoneTerrain::getInstance(900, 950, 320, 70);

    StoneTerrain *t11 = StoneTerrain::getInstance(333, 950, 200, 50);
    StoneTerrain *t12 = StoneTerrain::getInstance(651, 860, 200, 50);
    StoneTerrain *t13 = StoneTerrain::getInstance(75, 725, 200, 50);
    StoneTerrain *t14 = StoneTerrain::getInstance(465, 577, 200, 50);
    StoneTerrain *t15 = StoneTerrain::getInstance(144, 363, 200, 50);
    StoneTerrain *t16 = StoneTerrain::getInstance(349, 129, 200, 50);


    levels[0].push_back(bg);
    levels[0].push_back(t7);
    levels[0].push_back(t8);
    levels[0].push_back(t9);
    levels[0].push_back(t10);
    levels[0].push_back(t100);

    //levels[0].push_back(t0);
    levels[0].push_back(t1);
    levels[0].push_back(t2);
    levels[0].push_back(t3);
    levels[0].push_back(t4);
    levels[0].push_back(t5);
    levels[0].push_back(t6);
    levels[0].push_back(player);
    levels[0].push_back(heightLabel);

    levels[1].push_back(bg2);
    levels[1].push_back(t11);
    levels[1].push_back(t12);
    levels[1].push_back(t13);
    levels[1].push_back(t14);
    levels[1].push_back(t15);
    levels[1].push_back(t16);
    levels[1].push_back(player);
    levels[1].push_back(heightLabel);

    levels[2].push_back(bg);
    levels[2].push_back(player);
    levels[2].push_back(heightLabel);


    ses.setLevel(levels[0]);
    ses.run();

    return 0;
}



