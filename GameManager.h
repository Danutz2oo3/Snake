#pragma once
#include <iostream>
#include "Game.h"
#include "TextureLoader.h"

using namespace std;

class GameManager {
public:
    GameManager();
    ~GameManager();

    bool init();
    void run();
    bool loadMedia();

private:
    Game game;
};
