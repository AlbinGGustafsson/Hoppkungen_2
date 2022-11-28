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
    ~GameEngine();
private:
    static const int FPS = 60;

    std::vector<Sprite*> sprites;
    std::vector<Sprite*> added;
    std::vector<Sprite*> removed;
};

} // namespace cwing

#endif