#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::Load_texture(const char* name){
    SDL_Surface* tempSurface = IMG_Load(name);

    if (!tempSurface) {
        std::cout << "Failed to load image: " << name << " SDL_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!tex) {
        std::cout << "Failed to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
    }

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
