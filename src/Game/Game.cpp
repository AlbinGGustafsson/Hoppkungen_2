#include <SDL2/SDL.h>
#include "jEngine/Label.h"
#include "jEngine/GameEngine.h"
#include <string>
#include "jEngine/Player.h"
#include "Game/StoneTerrain.h"
#include "jEngine/Background.h"
#include "Game/Hoppkung.h"

#include <iostream>

using namespace jengine;
using namespace std;
using namespace constants;

GameEngine ses;
std::vector<std::vector<Sprite *>> levels;


class FinishTerrain : public StoneTerrain{
public:
    FinishTerrain(int x, int y, int w, int h, Label* label) : StoneTerrain(x, y, w, h), gameEventLabel(label) {}

    void aboveCollision(Player *p) override {
        Terrain::aboveCollision(p);
        gameEventLabel->setText("You won the game!");
    }
private:
    Label* gameEventLabel;
};


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
// Exempelkod för trampolinebeteende
//    void aboveCollision(Player *p) override {
//        p->setYCollision(true);
//        p->setYPosition(getRect().y + 10 - p->getRect().h);
//        p->setYVelocity(-p->getYVelocity());
//    }

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


class HeightLabel : public Label {
public:

    static HeightLabel* getInstance(int x, int y, int w, int h, HoppKung* p){
        return new HeightLabel(x, y, w, h, p);
    }

    void tick() {

        int height = player->getCurrentLevel() * WINDOW_HEIGHT + (WINDOW_HEIGHT - player->getYPosition() - PLAYER_HEIGHT);
        setText("Level: " + to_string(player->getCurrentLevel()) + " Height: " + to_string(height));
    }

protected:
    HeightLabel(int x, int y, int w, int h, HoppKung *p) : Label(x, y, w, h, ""), player(p) {}

private:
    HoppKung *player;

};



//Klass för karaktär för testning av olika nivåer
class FlyingDude : public HoppKung{

public:

    FlyingDude(int x, int y, int w, int h, vector<std::vector<Sprite *>> &lvls, GameEngine &session) : HoppKung(x, y, w, h, lvls,session) {}
    void gravity() override {
    }

    void spaceDown() override {}

    void spaceUp() override {}

    void leftDown() override {
        setXPosition(getXPosition() - 20);
    }

    void rightDown() override {
        setXPosition(getXPosition() + 20);
    }

    void leftUp() override {}

    void rightUp() override {}

    void tick() override {
        HoppKung::tick();
    }
    void upDown() override {
        setYPosition(getYPosition()-20);
    }
    void downDown() override {
        setYPosition(getYPosition()+20);
    }



protected:
};


int main(int argc, char **argv) {

   std::vector<Sprite *> level0;
    std::vector<Sprite *> level1;
    std::vector<Sprite *> level2;
    std::vector<Sprite *> level3;
    std::vector<Sprite *> level4;

    levels.push_back(level0);
    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);
    levels.push_back(level4);

    Background *bg0 = Background::getInstance(0, 0, 0, 0, "/levels/level0.png", "/levels/EloysKompis.mp3", 10);
    Background *bg1 = Background::getInstance(0, 0, 0, 0, "/levels/level1.png", "/levels/DkIsland.mp3", 128);
    Background *bg2 = Background::getInstance(0, 0, 0, 0, "/levels/level2.png", "/levels/Aquatic.mp3", 128);
    Background *bg3 = Background::getInstance(0, 0, 0, 0, "/levels/level3.png", "/levels/Aria.mp3", 128);
    Background *bg4 = Background::getInstance(0, 0, 0, 0, "/levels/level4.png", "/levels/Spacetime.mp3", 128);

    Label* gameEventLabel = Label::getInstance(500, 50, 200, 30, "");



    HoppKung *player = HoppKung::getInstance(100, 850, 100, PLAYER_HEIGHT, levels, ses);
    ses.changeSFXVolume(30);

    FinishTerrain* goal = new FinishTerrain(450, 150, 300, 50, gameEventLabel);

    StoneTerrain *t2 = StoneTerrain::getInstance(600, 660, 150, 50);
    StoneTerrain *t3 = StoneTerrain::getInstance(900, 450, 150, 50);
    StoneTerrain *t4 = StoneTerrain::getInstance(500, 260, 150, 50);
    StoneTerrain *t5 = StoneTerrain::getInstance(100, 260, 50, 50);

    HeightLabel *heightLabel = HeightLabel::getInstance(50,50,200,30, player);
    //StoneTerrain *t6 = MovingStoneTerrain::getInstance(900, 800, 200, 50);

    StoneTerrain *g1 = StoneTerrain::getInstance(-100, 950, 320, 70);
    StoneTerrain *g2 = StoneTerrain::getInstance(150, 950, 320, 70);
    StoneTerrain *g3 = StoneTerrain::getInstance(400, 950, 320, 70);
    StoneTerrain *g4 = StoneTerrain::getInstance(650, 950, 320, 70);
    StoneTerrain *g5 = StoneTerrain::getInstance(900, 950, 320, 70);

    StoneTerrain *t11 = StoneTerrain::getInstance(333, 950, 225, 50);
    StoneTerrain *t13 = StoneTerrain::getInstance(75, 725, 100, 50);
    StoneTerrain *t14 = StoneTerrain::getInstance(465, 577, 200, 50);
    StoneTerrain *t15 = StoneTerrain::getInstance(144, 400, 200, 50);
    StoneTerrain *t16 = StoneTerrain::getInstance(900, 363, 50, 50);
    StoneTerrain *t17 = StoneTerrain::getInstance(800, 120, 50, 50);

    //level 3
    StoneTerrain *L3_1 = StoneTerrain::getInstance(1100, 850, 225, 50);
    StoneTerrain *L3_2 = StoneTerrain::getInstance(770, 700, 50, 50);
    StoneTerrain *L3_3 = MovingStoneTerrain::getInstance(600, 400, 250, 50);
    StoneTerrain *L3_4 = StoneTerrain::getInstance(50, 200, 100, 50);
    StoneTerrain *L3_5 = StoneTerrain::getInstance(150, 15, 100, 50);
    StoneTerrain *L3_6 = StoneTerrain::getInstance(150, 0, 100, 50);


    //level 4
    StoneTerrain *L4_1 = MovingStoneTerrain::getInstance(600, 950, 250, 50);
    StoneTerrain *L4_2 = MovingStoneTerrain::getInstance(1000, 750, 250, 50);
    StoneTerrain *L4_3 = MovingStoneTerrain::getInstance(0, 550, 200, 50);
    StoneTerrain *L4_4 = StoneTerrain::getInstance(650, 400, 100, 50);
    StoneTerrain *L4_5 = StoneTerrain::getInstance(400, 250, 100, 50);
    StoneTerrain *L4_6 = StoneTerrain::getInstance(415, 100, 100, 50);
    StoneTerrain *L4_7 = StoneTerrain::getInstance(235, 250, 50, 50);
    StoneTerrain *blockStone1 = StoneTerrain::getInstance(500, 0, 50, 50);
    StoneTerrain *blockStone2 = StoneTerrain::getInstance(500, 50, 50, 50);


    // level 5
    StoneTerrain *L5_1 = StoneTerrain::getInstance(500, 950, 50, 50);
    StoneTerrain *L5_2 = StoneTerrain::getInstance(200, 700, 50, 50);
    StoneTerrain *L5_3 = StoneTerrain::getInstance(400, 450 , 50, 50);
    StoneTerrain *L5_4 = StoneTerrain::getInstance(650, 450, 50, 50);
    StoneTerrain *L5_5 = StoneTerrain::getInstance(800, 300, 50, 50);

    levels[0].push_back(bg0);
    levels[0].push_back(g1);
    levels[0].push_back(g2);
    levels[0].push_back(g3);
    levels[0].push_back(g4);
    levels[0].push_back(g5);


    levels[0].push_back(t2);
    levels[0].push_back(t3);
    levels[0].push_back(t4);
    levels[0].push_back(t5);
    levels[0].push_back(player);
    levels[0].push_back(heightLabel);
    levels[0].push_back(gameEventLabel);

    levels[1].push_back(bg1);
    levels[1].push_back(t11);
    levels[1].push_back(t13);
    levels[1].push_back(t14);
    levels[1].push_back(t15);
    levels[1].push_back(t16);
    levels[1].push_back(t17);
     levels[1].push_back(player);
    levels[1].push_back(heightLabel);
    levels[1].push_back(gameEventLabel);







    levels[2].push_back(bg2);
    levels[2].push_back(L3_1);
    levels[2].push_back(L3_2);
    levels[2].push_back(L3_3);
    levels[2].push_back(L3_4);
    levels[2].push_back(L3_5);
    levels[2].push_back(L3_6);
    levels[2].push_back(player);
    levels[2].push_back(heightLabel);
    levels[2].push_back(gameEventLabel);






    levels[3].push_back(bg3);
    levels[3].push_back(L4_1);
    levels[3].push_back(L4_2);
    levels[3].push_back(L4_3);
    levels[3].push_back(L4_4);
    levels[3].push_back(L4_5);
    levels[3].push_back(L4_6);
    levels[3].push_back(L4_7);
    levels[3].push_back(blockStone1);
    levels[3].push_back(blockStone2);
    levels[3].push_back(player);
    levels[3].push_back(heightLabel);
    levels[3].push_back(gameEventLabel);

    levels[4].push_back(bg4);
    levels[4].push_back(L5_1);
    levels[4].push_back(goal);
    levels[4].push_back(L5_2);
    levels[4].push_back(L5_3);
    levels[4].push_back(L5_4);
    levels[4].push_back(L5_5);
    levels[4].push_back(player);
    levels[4].push_back(heightLabel);
    levels[4].push_back(gameEventLabel);

    ses.setLevel(levels[0]);
    ses.run();

    return 0;
}



