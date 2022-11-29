#include <SDL2/SDL.h>
#include "Label.h"
#include "Button.h"
#include "GameEngine.h"
#include <string>
#include "Player.h"
#include "Terrain.h"
#include "Background.h"

#include <cstdlib>

using namespace jengine;
using namespace std;

int value = 0;
GameEngine ses;
std::vector<std::vector<Sprite*>> levels;
std::vector<Sprite*> level1;
std::vector<Sprite*> level2;

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



class PlayerDude: public Player{
public:

    int currentLevel = 0;

    PlayerDude():Player(600, 0, 100, 100) {}

    void tick() {

        if (getYPosition() < 0){

            ses.setLevel(levels[currentLevel+1]);
            currentLevel++;
            setYPosition(1200);
        }

        if (getYPosition() > 1200){
            ses.setLevel(levels[currentLevel-1]);
            currentLevel--;
            setYPosition(0);
        }


        if (getXPosition() + getRect().w > 1200){
            setXPosition(0);
        }

        if (getXPosition() < 0){
            setXPosition(1200 - getRect().w);
        }

        if (yDirection != 0) {
            currentTx = airTx;

            rect.x += xDirection;

        } else if (!(currentTx == leftTx || currentTx == rightTx || currentTx == downTx)) {
            currentTx = idelTx;
        }

        rect.y += yDirection;
    }
};



int main(int argc, char** argv){
//    Label* lbl = Label::getInstance(400, 100, 200, 70, "0");

    levels.push_back(level1);
    levels.push_back(level2);


    Background* bg = Background::getInstance(0,0,0,0);
    Player* player = new PlayerDude();
    Terrain* t0 = Terrain::getInstance(0, 1150 , 1200, 50, 3);
    Terrain* t1 = Terrain::getInstance(380, 900, 200, 50, 3);
    Terrain* t2 = Terrain::getInstance(600, 700, 200, 50, 3);
    Terrain* t3 = Terrain::getInstance(900, 450, 200, 50, 3);
    Terrain* t4 = Terrain::getInstance(600, 200, 200, 50, 3);
    Terrain* t5 = Terrain::getInstance(100, 380, 200, 50, 3);

    levels[0].push_back(bg);
    levels[0].push_back(player);
    levels[0].push_back(t0);
    levels[0].push_back(t1);
    levels[0].push_back(t2);
    levels[0].push_back(t3);
    levels[0].push_back(t4);
    levels[0].push_back(t5);

    levels[1].push_back(bg);
    levels[1].push_back(t4);
    levels[1].push_back(player);



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