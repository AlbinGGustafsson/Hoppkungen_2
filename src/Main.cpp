#include <SDL2/SDL.h>
#include "Label.h"
#include "Button.h"
#include "GameEngine.h"
#include <string>
#include "Player.h"
#include "Terrain.h"
#include "Background.h"

#include <cstdlib>
#include <iostream>

using namespace jengine;
using namespace std;

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


class MovingTerrain: public Terrain{
public:

    bool moveRight = true;

    MovingTerrain():Terrain(900, 800, 200, 50, 3){}

    void tick(){

        if (moveRight){
            if (rect.x < 995){
                rect.x+=3;
            }

            if (rect.x > 995){
                moveRight = false;
            }
        }

        if (!moveRight){

            if (rect.x > 5){
                rect.x-=3;
            }
            if (rect.x < 5){
                moveRight = true;
            }

        }

    }
};



class PlayerDude: public Player{
public:

    int currentLevel = 0;

    PlayerDude():Player(600, 110, 100, 100) {}

    void tick() {

        if (getYPosition() < 0){

            if (currentLevel + 1 + 1 <= levels.size()){
                ses.setLevel(levels[currentLevel+1]);
                currentLevel++;
                setYPosition(1200);
            }

        }

        if (getYPosition() > 1200){

            if (currentLevel - 1 >= 0){
                ses.setLevel(levels[currentLevel-1]);
                currentLevel--;
                setYPosition(0);
            }

        }


        if (getXPosition() + getRect().w > 1250){
            setXPosition(-50);
        }

        if (getXPosition() < -50){
            setXPosition(1250 - getRect().w);
        }

        if (yVelocity != 0) {
            currentTx = airTx;

            chargeJump = false;
            verticalCounter = 0;
            heightCounter = 0;

            rect.x += xVelocity;

        } else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idelTx;
        }

        rect.y += yVelocity;
    }
};



int main(int argc, char** argv){
//    Label* lbl = Label::getInstance(400, 100, 200, 70, "0");

    std::vector<Sprite*> level1;
    std::vector<Sprite*> level2;
    std::vector<Sprite*> level3;

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);


    Background* bg = Background::getInstance(0,0,0,0);
    Player* player = new PlayerDude();

    Terrain* t0 = Terrain::getInstance(-100, 1150 , 1400, 50, 3);
    Terrain* t1 = Terrain::getInstance(380, 900, 200, 50, 3);
    Terrain* t2 = Terrain::getInstance(600, 700, 200, 50, 3);
    Terrain* t3 = Terrain::getInstance(900, 450, 200, 50, 3);
    Terrain* t4 = Terrain::getInstance(600, 220, 200, 50, 3);
    Terrain* t5 = Terrain::getInstance(100, 380, 200, 50, 3);

    Terrain* t6 = new MovingTerrain();
    Terrain* t7 = Terrain::getInstance(0, 1200-700, 50, 700, 1);
    Terrain* t8 = Terrain::getInstance(1200, 1200-700, 50, 700, 1);

    Terrain* t11 = Terrain::getInstance(333, 1146, 200, 50, 3);
    Terrain* t12 = Terrain::getInstance(651, 860, 200, 50, 3);
    Terrain* t13 = Terrain::getInstance(75, 725, 200, 50, 3);
    Terrain* t14 = Terrain::getInstance(465, 577, 200, 50, 3);
    Terrain* t15 = Terrain::getInstance(144, 363, 200, 50, 3);
    Terrain* t16 = Terrain::getInstance(349, 129, 200, 50, 3);


    levels[0].push_back(bg);
    levels[0].push_back(t0);
    levels[0].push_back(t1);
    levels[0].push_back(t2);
    levels[0].push_back(t3);
    levels[0].push_back(t4);
    levels[0].push_back(t5);
    levels[0].push_back(t6);
    levels[0].push_back(t7);
    levels[0].push_back(t8);
    levels[0].push_back(player);

    levels[1].push_back(bg);
    levels[1].push_back(t11);
    levels[1].push_back(t12);
    levels[1].push_back(t13);
    levels[1].push_back(t14);
    levels[1].push_back(t15);
    levels[1].push_back(t16);
    levels[1].push_back(player);

    levels[2].push_back(bg);
    levels[2].push_back(player);




    //Terrain* t2 = Terrain::getInstance(250, 1100, 200, 50, 3);

//    TickLabel* labelTest = new TickLabel();
//
//    Button* b1 = new incButton(lbl);
//    Button* b2 = new decButton(lbl);
//    Button* b3 = new randomButton(lbl);
//    auto* b4 = new RemoveButton(labelTest);

//    ses.add(lbl);
//    ses.add(b1);
//    ses.add(b2);
//    ses.add(b3);
//    ses.add(labelTest);
//    ses.add(b4);

//    ses.add(bg);
//    ses.add(player);
//    ses.add(t0);
//    ses.add(t1);
//    ses.add(t2);
//    ses.add(t3);
//    ses.add(t4);
//    ses.add(t5);

//    ses.add(t3);
//    ses.add(t4);
//    ses.add(t5);

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