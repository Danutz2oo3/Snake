#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Snake.h"
#include "Food.h"

using namespace std;

class Game {
public:
    Game();
    ~Game();

    bool init();
    void close();
    void handleInput();
    void moveSnake();
    void checkCollisionWithFood();
    void render();
    bool loadMedia();
    bool checkCollisionWithWalls();
    bool checkSelfCollision();
    void spawnFood();

    bool isGameOver() const;
    void setGameOver(bool value);

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SNAKE_SIZE = 20;

    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    Snake snake;
    Food food;

    SDL_Texture* snake_texture;
    SDL_Texture* food_texture;
    SDL_Texture* game_over_texture;

    SDL_Rect game_over_rect;

    int direction_x;
    int direction_y;

    bool game_over;
};
