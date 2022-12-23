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


int main(int argc, char **argv) {

    std::vector<Sprite *> level1;
    std::vector<Sprite *> level2;
    std::vector<Sprite *> level3;

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);


    Background *bg = Background::getInstance(0, 0, 0, 0, "bg1.png", "bgMusic1.mp3", 10);
    Background *bg2 = Background::getInstance(0, 0, 0, 0, "bg2.png", "bgMusic2.mp3", 128);

    //HoppKungen *player = HoppKungen::getInstance(600, 110, 100, 100);
    HoppKung *player = HoppKung::getInstance(600, 110, 100, 100, levels, ses);

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



