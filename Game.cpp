#include "Game.h"
#include "TextureLoader.h"

Game::Game() : g_window(nullptr), g_renderer(nullptr), snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SNAKE_SIZE), game_over(false) {
    game_over_rect.x = (SCREEN_WIDTH - 320) / 2;
    game_over_rect.y = (SCREEN_HEIGHT - 240) / 2;
    game_over_rect.w = 320;
    game_over_rect.h = 240;

    spawnFood();

    direction_x = 1;
    direction_y = 0;
}

Game::~Game() {}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not be initialized\n";
        return false;
    }

    g_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == nullptr) {
        cerr << "Window could not be created: " << SDL_GetError() << "\n";
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == nullptr) {
        cerr << "Renderer could not be created: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void Game::close() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
}

void Game::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            exit(0);
        }
    }

    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

    if (current_key_states[SDL_SCANCODE_UP] && direction_y == 0) {
        direction_x = 0;
        direction_y = -1;
    }
    if (current_key_states[SDL_SCANCODE_DOWN] && direction_y == 0) {
        direction_x = 0;
        direction_y = 1;
    }
    if (current_key_states[SDL_SCANCODE_LEFT] && direction_x == 0) {
        direction_x = -1;
        direction_y = 0;
    }
    if (current_key_states[SDL_SCANCODE_RIGHT] && direction_x == 0) {
        direction_x = 1;
        direction_y = 0;
    }
}

void Game::spawnFood() {
    food.x = rand() % (SCREEN_WIDTH / SNAKE_SIZE) * SNAKE_SIZE;
    food.y = rand() % (SCREEN_HEIGHT / SNAKE_SIZE) * SNAKE_SIZE;
}

void Game::moveSnake() {
    int new_x = snake.getSegments()[0].x + direction_x * SNAKE_SIZE;
    int new_y = snake.getSegments()[0].y + direction_y * SNAKE_SIZE;

    SnakeSegment new_head = {new_x, new_y};
    snake.getSegments().insert(snake.getSegments().begin(), new_head);

    snake.getSegments().pop_back();
}

void Game::checkCollisionWithFood() {
    SnakeSegment& head = snake.getSegments()[0];
    if (head.x == food.x && head.y == food.y) {
        SnakeSegment tail = snake.getSegments().back();
        snake.getSegments().push_back({tail.x, tail.y});

        spawnFood();
    }
}

void Game::render() {
    SDL_RenderClear(g_renderer);

    if (game_over) {
        SDL_RenderCopy(g_renderer, game_over_texture, NULL, &game_over_rect);
    } else {
        for (size_t i = 0; i < snake.getSegments().size(); i++) {
            SDL_Rect snake_rect = {snake.getSegments()[i].x, snake.getSegments()[i].y, SNAKE_SIZE, SNAKE_SIZE};
            SDL_RenderCopy(g_renderer, snake_texture, NULL, &snake_rect);
        }

        SDL_Rect food_rect = {food.x, food.y, SNAKE_SIZE, SNAKE_SIZE};
        SDL_RenderCopy(g_renderer, food_texture, NULL, &food_rect);
    }

    SDL_RenderPresent(g_renderer);
    SDL_Delay(80);
}

bool Game::loadMedia() {
    game_over_texture = loadTexture(g_renderer, "src/SDL2/resources/gameover.png");
    if (game_over_texture == nullptr) {
        cerr << "Failed to load gameover.png!!\n";
        return false;
    }

    snake_texture = loadTexture(g_renderer, "src/SDL2/resources/snake.bmp");
    if (snake_texture == nullptr) {
        cerr << "Failed to load snake.bmp!!\n";
        return false;
    }

    food_texture = loadTexture(g_renderer, "src/SDL2/resources/food.bmp");
    if (food_texture == nullptr) {
        cerr << "Failed to load food.bmp!!\n";
        return false;
    }

    return true;
}

bool Game::checkCollisionWithWalls() {
    const SnakeSegment& head = snake.getSegments()[0];
    return (head.x < 0 || head.x >= SCREEN_WIDTH || head.y < 0 || head.y >= SCREEN_HEIGHT);
}

bool Game::checkSelfCollision() {
    const SnakeSegment& head = snake.getSegments()[0];

    for (size_t i = 1; i < snake.getSegments().size(); i++) {
        if (head.x == snake.getSegments()[i].x && head.y == snake.getSegments()[i].y) {
            return true;
        }
    }

    return false;
}

bool Game::isGameOver() const {
    return game_over;
}

void Game::setGameOver(bool value) {
    game_over = value;
}
