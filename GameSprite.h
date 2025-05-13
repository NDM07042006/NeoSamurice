#ifndef GAMESPRITE_H_INCLUDED
#define GAMESPRITE_H_INCLUDED
#include "game.h"
#include "EntityComponentSystem.h"
#include <SDL.h>
#include <SDL_image.h>


class SpriteComponent: public Component{
private:
    PositionComponent *Position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    int scale;

    bool animated = false;
    int frames = 0;
    int speed = 100;


public:
    SpriteComponent() = default;
    SpriteComponent(const char* path, int sca){
        scale = sca;
        setTex(path);

    }
    SpriteComponent(const char* path,int sca, int nFrames, int mSpeed){

        scale = sca;
        animated = true;
        frames = nFrames;
        speed = mSpeed;
        setTex(path);

        if (!path) {
    std::cerr << "Failed to load image: " << path << " | " << IMG_GetError() << std::endl;
    exit(1); // or return gracefully
}

    }
    void setTex(const char* path) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    texture = TextureManager::Load_texture(path);
}


    ~SpriteComponent() {
    if (texture) {
        if (texture != nullptr);
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

    void setFrame(int nFrames){
        frames = nFrames;
    }

    void setSpeed(int mSpeed){
        speed = mSpeed;
    }

    void init() override {
        Position = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = Position->width * scale;
        srcRect.h = Position->height * scale;

    }

    void update() override {

        if (animated && Position->side_faccing == 1 && !Position->Is_jumping){
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
        }
        else if (animated && Position->side_faccing == -1 && !Position->Is_jumping){
            srcRect.x = srcRect.w * (frames - static_cast<int>((SDL_GetTicks()/speed)%frames));
        }
        else if (animated && Position->side_faccing == -1 && Position->Is_jumping){
            srcRect.x = srcRect.w * (frames - static_cast<int>((SDL_GetTicks()/speed)%frames));
        }
        else if (animated && Position->side_faccing == 1 && Position->Is_jumping){
            srcRect.x = srcRect.w * (frames - static_cast<int>((SDL_GetTicks()/speed)%frames));
        }


        destRect.x = static_cast<int>(Position->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(Position->position.y);
        destRect.w = Position->width * Position->scale;
        destRect.h = Position->height * Position->scale;
    }

    void draw() override {



        TextureManager::Draw(texture, srcRect, destRect);
    }


};

#endif // GAMESPRITE_H_INCLUDED
