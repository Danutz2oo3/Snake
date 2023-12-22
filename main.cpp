#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SNAKE_SIZE = 20;

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

struct snake_segment{
    int x,y;
};

typedef struct food{
    int x;
    int y;
}Food;

Food food;

vector<snake_segment> snake;

SDL_Texture *load_texture(const string &path);
SDL_Texture *snake_texture = NULL;
SDL_Texture *food_texture = NULL;

int direction_x = 1;//snake initial movement direction
int direction_y = 0;

bool init(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cerr << "SDL could not be initialized\n";
        return false;
    }
    g_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(g_window == NULL){
        cerr << "Window could not be created: " << SDL_GetError() << "\n";
        return false;
    }
    g_renderer = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);

    if(g_renderer == NULL){
        cerr << "Renderer could not be created: " << SDL_GetError() << "\n";
    }

    return true;
}

void close(){
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
}

void move_snake(){
    int new_x = snake[0].x + direction_x * SNAKE_SIZE;
    int new_y = snake[0].y + direction_y * SNAKE_SIZE;

    snake_segment new_head = {new_x,new_y};
    snake.insert(snake.begin(),new_head);

    snake.pop_back();
}

void spawn_food(){
    //generate random positions for the food within screen boundaries
    food.x = rand() % (SCREEN_WIDTH/SNAKE_SIZE)*SNAKE_SIZE;
    food.y = rand() % (SCREEN_HEIGHT/SNAKE_SIZE)*SNAKE_SIZE;
}

void handle_input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)!=0){
        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
            exit(0);
        }
    }
    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

    if(current_key_states[SDL_SCANCODE_UP] && direction_y == 0){
        direction_x = 0;
        direction_y = -1;
    }
    if(current_key_states[SDL_SCANCODE_DOWN] && direction_y == 0){
        direction_x = 0;
        direction_y = 1;
    }
    if(current_key_states[SDL_SCANCODE_LEFT] && direction_x == 0){
        direction_x = -1;
        direction_y = 0;
    }
    if(current_key_states[SDL_SCANCODE_RIGHT] && direction_x == 0){
        direction_x = 1;
        direction_y = 0;
    }

}

bool load_media(){
    snake_texture = load_texture("snake.bmp");
    if(snake_texture == NULL){
        cerr << "Failed to load snake.bmp!!\n";
        return false;
    }
    food_texture = load_texture("food.bmp");
    if(food_texture == NULL){
        cerr << "Failed to load food.bmp!!\n";
        return false;
    }
    return true;
}

SDL_Texture *load_texture(const string &path){
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());

    if(load_surface == NULL){
        cout << "Unable to load image " << path.c_str() << " !SDL_Image ERROR " << IMG_GetError() << "\n";
        return NULL;
    }
    new_texture = SDL_CreateTextureFromSurface(g_renderer,load_surface);

    if(new_texture == NULL){
        cerr << "Unable to create Texture from Surface";
        return NULL;
    }
    SDL_FreeSurface(load_surface);

    return new_texture;
}

void render_snake(){
    for(size_t i=0; i<snake.size();i++){
        SDL_Rect snake_rect = {snake[i].x,snake[i].y,SNAKE_SIZE,SNAKE_SIZE};
        SDL_RenderCopy(g_renderer,snake_texture,NULL,&snake_rect);

    }
}

bool check_collision_with_food(){
    snake_segment &head = snake[0];
    if(head.x == food.x && head.y == food.y){
        snake_segment tail = snake.back();
        snake.push_back({tail.x,tail.y});

        spawn_food();
    }
    return false;
}

bool check_collision_with_walls(){
    snake_segment &head = snake[0];//get reference to the head of the snake
    if(head.x<0 || head.x>=SCREEN_WIDTH || head.y<0 || head.y>=SCREEN_HEIGHT){
        return true;
    }
    return false;
}

bool check_self_collision(){
    snake_segment &head = snake[0];

    //iterate through the body segments of the snake

    for(size_t i = 1; i < snake.size(); i++){
        
    }
}

int main(int argc, char *args[])
{
    if(!init()){
        cerr << "Initialization Failed\n";
    }
    if(!load_media()){
        cerr << "Failed to load Media!\n";
        return 1;
    }
    snake.push_back({SCREEN_WIDTH/2,SCREEN_HEIGHT/2});
    spawn_food();
    bool quit = false;

    while(!quit){
        handle_input();
        move_snake();

        if(check_collision_with_walls()){
            quit = true;
        }

        check_collision_with_food();

        SDL_RenderClear(g_renderer);

        render_snake();

        SDL_Rect food_rect {food.x, food.y, SNAKE_SIZE, SNAKE_SIZE};
        SDL_RenderCopy(g_renderer,food_texture,NULL,&food_rect);

        SDL_RenderPresent(g_renderer);
        SDL_Delay(100);
    }
    close();
    return 0;
}
