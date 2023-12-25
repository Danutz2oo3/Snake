#include "GameManager.h"

int main(int argc, char *args[]) {
    GameManager gameManager;
    if (!gameManager.init()) {
        cerr << "Initialization Failed\n";
        return 1;
    }

    if (!gameManager.loadMedia()) {
        cerr << "Failed to load Media!\n";
        return 1;
    }

    gameManager.run();
    
    return 0;
}
