#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants
{
    //gResPath-contains the relative path to your resources.
    const std::string gResPath="./resources/";

    //fps
    static const int FPS = 60;

    //sound constants
    static const int MUSIC_CHANNEL = 0;
    static const int WALKING_CHANNEL = 1;
    static const int JUMP_CHANNEL = 2;
    static const int JUMP_CHARGE_CHANNEL = 3;
    static const int EMPTY_CHANNEL = 5;

    //physics constants
    static const int MAX_PLAYER_DOWNWARD_VELOCITY = 15;
    static const int PLAYER_DOWNWARD_VELOCITY_GROWTH = 1;
    static const int MAX_DOWNWARD_BOUNCE_VELOCITY = 10;
    static const int MIN_DOWNWARD_BOUNCE_VELOCITY = 5;
    static const int JUMP_VELOCITY = 30;
    static const int HORIZONTAL_MOVEMENT = 20;


    static const int WINDOW_HEIGHT = 1000;
    static const int WINDOW_WIDTH = 1200;
}

#endif