#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"
#include "Player.h"


namespace jengine {

class GameEngine {
public:
    void add(Sprite* s);
    void remove(Sprite* s);
    void run();

    void setLevel(std::vector<Sprite*> level);

    void changeSFXVolume(int volume) const;

    ~GameEngine();
private:
    std::vector<Sprite*> sprites;
    std::vector<Sprite*> added;
    std::vector<Sprite*> removed;
};

} // namespace cwing

#endif