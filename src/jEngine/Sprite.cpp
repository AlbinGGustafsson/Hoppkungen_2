#include "jEngine/Sprite.h"

namespace jengine{

    Sprite::Sprite(int x, int y, int w, int h): rect{x, y, w, h}{
        xVelocity = 0;
        yVelocity = 0;
        yCollision = false;
        xCollision = false;

    }

    int Sprite::getXPosition() const{
        return rect.x;
    }
    int Sprite::getYPosition() const{
        return rect.y;
    }
    void Sprite::setXPosition(int x) {
        rect.x = x;
    }
    void Sprite::setYPosition(int y) {
        rect.y = y;
    }

    void Sprite::setXCollision(bool collision) {
        xCollision = collision;
    }

    void Sprite::setYCollision(bool collision) {
        yCollision = collision;
    }

    void Sprite::resetYVelocity() {
        yVelocity = 0;
    }

    void Sprite::resetXVelocity(){
        xVelocity = 0;
    }

    void Sprite::changeYVelocity(int y) {
        yVelocity += y;
    }

    void Sprite::changeXVelocity(int x) {
        xVelocity += x;
    }

    int Sprite::getXVelocity() const{
        return xVelocity;
    }

    int Sprite::getYVelocity() const{
        return yVelocity;
    }

    void Sprite::setYVelocity(int y){
        yVelocity = y;
    }
    void Sprite::setXVelocity(int x){
        xVelocity = x;
    }

    bool Sprite::getXCollision() const{
        return xCollision;
    }
    bool Sprite::getYCollision() const{
        return yCollision;
    }

    //måste vara implementerad för att den är virtual deklarerad
    Sprite::~Sprite(){}


    void Sprite::checkCollision(Sprite* other) {
        if (SDL_HasIntersection(&getRect(), &other->getRect())) {
            other->collision(this);
        }
    }


}

