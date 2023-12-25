#include "TextureLoader.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        cerr << "Unable to load image " << path.c_str() << "! SDL_Image ERROR " << IMG_GetError() << "\n";
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (newTexture == nullptr) {
        cerr << "Unable to create Texture from Surface";
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);

    return newTexture;
}
