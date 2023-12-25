#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
