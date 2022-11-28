#include <SDL2/SDL.h>
#include "Label.h"
#include "System.h"
#include "Button.h"
#include "GameEngine.h"
#include <string>

#include <cstdlib>

using namespace jengine;
using namespace std;

int value = 0;
GameEngine ses;

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


int main(int argc, char** argv){
//    Label* lbl = Label::getInstance(400, 100, 200, 70, "0");

    Background* bg = Background::getInstance(0,0,0,0);
    Player* player = Player::getInstance(250, 0, 100, 100);
    Terrain* t1 = Terrain::getInstance(250, 1100, 200, 50, 3);
    Terrain* t2 = Terrain::getInstance(380, 900, 200, 50, 3);
//    Terrain* t3 = Terrain::getInstance(570, 700, 200, 50, 3);
//    Terrain* t4 = Terrain::getInstance(700, 550, 130, 50, 2);
//    Terrain* t5 = Terrain::getInstance(570, 400, 70, 50, 1);


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
    ses.add(bg);
    ses.add(player);
    ses.add(t1);
    ses.add(t2);
//    ses.add(t3);
//    ses.add(t4);
//    ses.add(t5);

    ses.run();

    return 0;
}