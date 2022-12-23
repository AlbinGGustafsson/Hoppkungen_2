#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Sprite.h"
#include "Player.h"
#include <unordered_map>


namespace jengine {

    typedef void(*hotkeyFunction)();

class GameEngine {
public:
    void add(Sprite* s); //Skulle användas om något ska läggas till när spelloopen körs.
    void remove(Sprite* s);
    void run();

    void setLevel(std::vector<Sprite*> level);

    void hotkey(SDL_Event& event);
    void changeSFXVolume(int volume) const;

    void addHotkey(hotkeyFunction f, SDL_Keycode k);


    ~GameEngine();
private:
    std::vector<Sprite*> sprites;
    std::vector<Sprite*> added;
    std::vector<Sprite*> removed;

    std::unordered_map<SDL_Keycode, hotkeyFunction> hotkeyFunctionMap;
};

} // namespace cwing

#endif