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


class HeightLabel : public Label {
public:

    static HeightLabel* getInstance(int x, int y, int w, int h, HoppKung* p){
        return new HeightLabel(x, y, w, h, p);
    }

    void tick() {

        int height = player->getCurrentLevel() * WINDOW_HEIGHT + (1200 - player->getYPosition());
        setText(to_string(height));
    }

protected:
    HeightLabel(int x, int y, int w, int h, HoppKung *p) : Label(x, y, w, h, ""), player(p) {}

private:
    HoppKung *player;

};




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


    FlyingDude *player = new FlyingDude(600, 110, 100, 100, levels, ses);
    //HoppKung *player = HoppKung::getInstance(600, 110, 100, 100, levels, ses);
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


    levels[0].push_back(bg0);
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

    levels[1].push_back(bg1);

    levels[1].push_back(t11);
    levels[1].push_back(t12);
    levels[1].push_back(t13);
    levels[1].push_back(t14);
    levels[1].push_back(t15);
    levels[1].push_back(t16);
    levels[1].push_back(player);
    levels[1].push_back(heightLabel);

    levels[2].push_back(bg2);
    levels[2].push_back(player);
    levels[2].push_back(heightLabel);

    levels[3].push_back(bg3);
    levels[3].push_back(player);
    levels[3].push_back(heightLabel);

    levels[4].push_back(bg4);
    levels[4].push_back(player);
    levels[4].push_back(heightLabel);

    ses.setLevel(levels[0]);
    ses.run();

    return 0;
}



