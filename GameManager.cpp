#include "GameManager.h"

GameManager::GameManager() {}

GameManager::~GameManager() {}

bool GameManager::init() {
    return game.init();
}

void GameManager::run() {
    bool quit = false;

    while (!quit) {
        game.handleInput();
        game.moveSnake();

        if (game.checkCollisionWithWalls() || game.checkSelfCollision()) {
            game.setGameOver(true);
        }

        if (!game.isGameOver()) {
            game.checkCollisionWithFood();
        }

        game.render();
    }

    game.close();
}

bool GameManager::loadMedia() {
    return game.loadMedia();
}
