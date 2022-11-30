#include "Sprite.h"

namespace jengine{

Sprite::Sprite(int x, int y, int w, int h): rect{x, y, w, h}{}

    int Sprite::getXPosition(){
        return rect.x;
    }
    int Sprite::getYPosition(){
        return rect.y;
    }


//måste vara implementerad för att den är virtual deklarerad
Sprite::~Sprite(){}





}

