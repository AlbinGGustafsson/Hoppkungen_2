#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Label.h"
#include "Button.h"
#include "GameEngine.h"
#include <string>
#include "Player.h"
#include "SciFiTerrain.h"
#include "Background.h"
#include "Amongus.h"
#include "System.h"

#include <cstdlib>
#include <iostream>

using namespace jengine;
using namespace std;
using namespace constants;

static const int WINDOW_HEIGHT = 1200;
static const int WINDOW_WIDTH = 1200;

int value = 0;
GameEngine ses;
std::vector<std::vector<Sprite*>> levels;

class incButton: public Button{
public:
    incButton(Label* lbl):Button(100, 100, 200, 70, "Increase"), label(lbl){}
    
    void perform(Button* source){
        value++;
        label->setText(to_string(value));
    }

private:
    Label* label;

};

class decButton: public Button{
public:
    decButton(Label* lbl):Button(100, 200, 200, 70, "Decrease"), label(lbl){}
    
    void perform(Button* source){
        value--;
        label->setText(to_string(value));
    }

private:
    Label* label;

};

class randomButton: public Button{
public:

    randomButton(Label* lbl):Button(300, 300, 200, 70, "Random"){}
    
    void perform(Button* source){
        int randomValue = rand() % 100;
        source->setText(to_string(randomValue));
    }
};


class RemoveButton: public Button{
public:

    RemoveButton(Sprite* sprite):Button(550, 550, 150, 50, "Remove"), s(sprite){}
    void perform(Button* source){
        ses.remove(s);
    }

private:
    Sprite *s;

};


class TickLabel: public Label{
public:

    TickLabel():Label(500, 500, 50, 30, "tick"){}


    int counter = 0;
    void tick(){

        setText(to_string(counter));
        counter++;

    }
};


class MovingTerrain: public SciFiTerrain{
public:

    bool moveRight = true;

    MovingTerrain(): SciFiTerrain(900, 800, 200, 50, 3){}

    void collision(Sprite *other) override {
        Terrain::collision(other);

        if (Terrain* ot = dynamic_cast<Terrain*>(other)){
            cout << "krock" << endl;
        }

    }


    void aboveCollision(Player *p) override {

        p->setYCollision(true);
        p->setYPosition(getRect().y + 10 - p->getRect().h);
        p->setYVelocity(-p->getYVelocity());

//        Terrain::aboveCollision(p);
//        std::cout << "special collision" << std::endl;
    }


    void tick(){

        if (moveRight){
            if (getRect().x < 995){
                setXPosition(getXPosition() + 3);
            }

            if (getRect().x > 995){
                moveRight = false;
            }
        }

        if (!moveRight){

            if (getRect().x > 5){
                setXPosition(getXPosition() - 3);
            }
            if (getRect().x < 5){
                moveRight = true;
            }

        }

    }
};


class TestPlayer: public Player{
public:

    TestPlayer():Player(600, 110, 100, 100){
        texture = IMG_LoadTexture(sys.getRenderer(), (constants::gResPath + "images/player/air.png").c_str());
    }

    void draw() const override {
        SDL_RenderCopy(sys.getRenderer(), texture, nullptr, &getRect());
    }

    void leftDown() override {
        if (!getXCollision()){
            setXPosition(getXPosition() - HORIZONTAL_MOVEMENT * 2);
        }
    }

private:
    SDL_Texture* texture;

};


class PlayerDude: public Amongus {
public:

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

    PlayerDude():Amongus(600, 110, 100, 100) {
        chargingJump = false;
        horizontalCounter = 0;
        verticalCounter = 0;
    }


    void spaceDown() override {

        //Börjar ladda ett hopp om man står på en platform.
        if (getYCollision()) {
            if (!chargingJump){
                chargingJump = true;
                std::cout << "charging jump" << std::endl;
                verticalCounter+=INITIAL_VERTICAL_CHARGE_VELOCITY;

                Mix_PlayChannel(JUMP_CHARGE_CHANNEL, jumpChargeSFX, 0);
            }

            //Om man fortsätter hålla in space ökar laddningen av hoppet.
            if (verticalCounter < MAX_PLAYER_VERTICAL_CHARGE_VELOCITY){
                verticalCounter+=PLAYER_VERTICAL_CHARGE_GROWTH;
                std::cout << "hc: " << verticalCounter << std::endl;
            }else{
                std::cout << "max vertical charge charge" << std::endl;
            }

            currentTx = downTx;

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
            Mix_PlayChannel(JUMP_CHANNEL, jumpSFX, 0);
        }

    }

    void leftDown() override {

        //Spelaren går till vänster, sätter texture och spelar ljudeffekt om man inte är i luften och inte laddar ett hopp och inte har en kollision med en vägg.
        if (!chargingJump && getYVelocity() == 0 && !getXCollision()){
            setXPosition(getXPosition() - HORIZONTAL_MOVEMENT);
            currentTx = leftTx;
            if (Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }

        //Logik för att kalkylera hur långt vänster ett hopp ska ske
        if (chargingJump){
            if (horizontalCounter == 0){
                horizontalCounter-=INITIAL_HORIZONTAL_CHARGE_VELOCITY;
                std::cout << "vc: " << horizontalCounter << std::endl;
            }else if (horizontalCounter < MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY && horizontalCounter > -MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY){
                horizontalCounter-=PLAYER_HORIZONTAL_CHARGE_GROWTH;
                std::cout << "vc: " << horizontalCounter << std::endl;
            }else{
                std::cout << "max horizontal charge" << std::endl;
            }

        }

    }

    void rightDown() override {

        //Spelaren går till höger, sätter texture och spelar ljudeffekt om man inte är i luften och inte laddar ett hopp och inte har en kollision med en vägg.
        if (!chargingJump && getYVelocity() == 0 && !getXCollision()){
            setXPosition(getXPosition() + HORIZONTAL_MOVEMENT);
            currentTx = rightTx;
            if (Mix_Playing(WALKING_CHANNEL) == 0){
                Mix_PlayChannel(WALKING_CHANNEL, walkingSFX, 0);
            }
        }


        //Logik för att kalkylera hur långt höger ett hopp ska ske
        if (chargingJump){
            if (horizontalCounter == 0){
                horizontalCounter+=INITIAL_HORIZONTAL_CHARGE_VELOCITY;
                std::cout << "vc: " << horizontalCounter << std::endl;
            }else if (horizontalCounter < MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY && horizontalCounter > -MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY){
                horizontalCounter+=PLAYER_HORIZONTAL_CHARGE_GROWTH;
                std::cout << "vc: " << horizontalCounter << std::endl;
            }else{
                std::cout << "max horizontal charge" << std::endl;
            }
        }
    }

    void leftUp() override {
        if (!chargingJump){
            currentTx = idleTx;
        }
    }

    void rightUp() override {
        if (!chargingJump){
            currentTx = idleTx;
        }
    }


    void tick() override {

        //Byter level när spelaren flyttar upp ovanför fönstret
        if (getYPosition() < 0){
            if ((currentLevel + 1) < static_cast<int>(levels.size())){
                ses.setLevel(levels[currentLevel+1]);
                currentLevel++;
                setYPosition(WINDOW_HEIGHT);
            }
        }

        //Byter level när spelaren flyttar ned under fönstret
        if (getYPosition() > WINDOW_HEIGHT){
            if (currentLevel - 1 >= 0){
                ses.setLevel(levels[currentLevel-1]);
                currentLevel--;
                setYPosition(0);
            }

        }

        //spelaren flyttar till andra sidan när den går utanför till höger
        if (getXPosition() + getRect().w > WINDOW_WIDTH + getRect().w/2){
            setXPosition(-getRect().w/2);
        }

        //spelaren flyttar till andra sidan när den går utanför till vänster
        if (getXPosition() < -getRect().w/2){
            setXPosition(WINDOW_WIDTH + getRect().w/2 - getRect().w);
        }

        //När man är i luften så sätter den spelarens texture till air och ett hopp återställs.
        if (getYVelocity() != 0) {
            currentTx = airTx;


            Mix_HaltChannel(JUMP_CHARGE_CHANNEL);
            chargingJump = false;
            horizontalCounter = 0;
            verticalCounter = 0;

            rect.x += xVelocity;

            //Återställer texture till idle när man landar
        } else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idleTx;
        }

        setYPosition(getYPosition() + getYVelocity());
    }

    int getCurrentLevel() const{
        return currentLevel;
    }


};


class HeightLabel: public Label{
public:

    HeightLabel(PlayerDude* p):Label(50, 50, 50, 30, "0"), player(p){}

    void tick(){

        int height = player->getCurrentLevel()*WINDOW_HEIGHT + (1200-player->getYPosition());
        setText(to_string(height));
    }
    PlayerDude* player;
};




int main(int argc, char** argv){
//    Label* lbl = Label::getInstance(400, 100, 200, 70, "0");

    std::vector<Sprite*> level1;
    std::vector<Sprite*> level2;
    std::vector<Sprite*> level3;

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);


    Background* bg = Background::getInstance(0,0,0,0, "bg1.png", "bgMusic1.mp3", 10);
    Background* bg2 = Background::getInstance(0,0,0,0, "bg2.png", "bgMusic2.mp3", 128);

    PlayerDude* player = new PlayerDude();
    ses.changeSFXVolume(30);
    //Player* player = Player::getInstance(600, 110, 100, 100);
    //TestPlayer* player = new TestPlayer();

    SciFiTerrain* t0 = SciFiTerrain::getInstance(-100, 1150 , 1400, 50, 3);
    SciFiTerrain* t1 = SciFiTerrain::getInstance(380, 900, 200, 50, 3);
    SciFiTerrain* t2 = SciFiTerrain::getInstance(600, 700, 200, 50, 3);
    SciFiTerrain* t3 = SciFiTerrain::getInstance(900, 450, 200, 50, 3);
    SciFiTerrain* t4 = SciFiTerrain::getInstance(600, 220, 200, 50, 3);
    SciFiTerrain* t5 = SciFiTerrain::getInstance(100, 380, 200, 50, 3);

    HeightLabel* heightLabel = new HeightLabel(player);
    SciFiTerrain* t7 = SciFiTerrain::getInstance(0, 1200-700, 50, 700, 3);

    SciFiTerrain* t6 = new MovingTerrain();

    SciFiTerrain* t11 = SciFiTerrain::getInstance(333, 1146, 200, 50, 3);
    SciFiTerrain* t12 = SciFiTerrain::getInstance(651, 860, 200, 50, 3);
    SciFiTerrain* t13 = SciFiTerrain::getInstance(75, 725, 200, 50, 3);
    SciFiTerrain* t14 = SciFiTerrain::getInstance(465, 577, 200, 50, 3);
    SciFiTerrain* t15 = SciFiTerrain::getInstance(144, 363, 200, 50, 3);
    SciFiTerrain* t16 = SciFiTerrain::getInstance(349, 129, 200, 50, 3);



    levels[0].push_back(bg);
    levels[0].push_back(t0);
    levels[0].push_back(t1);
    levels[0].push_back(t2);
    levels[0].push_back(t3);
    levels[0].push_back(t4);
    levels[0].push_back(t5);
    levels[0].push_back(t6);
    levels[0].push_back(t7);
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


    cout << "after run" << endl;


    levels.clear();
    level1.clear();
    level2.clear();

    delete player;
    delete t0;
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete bg;


    return 0;
}