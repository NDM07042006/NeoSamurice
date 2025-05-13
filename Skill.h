#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED




#include <SDL.h>
#include <SDL_image.h>
#include "GameStat.h"
#include "PositionComponent.h"
#include "Component.h"
#include "game.h"

class Skill : public Component {

public:
    PositionComponent* player ;

    SDL_Rect srcR;
    SDL_Rect destRect;

    SDL_Texture* texture;

    SDL_Point center = { 32 / 2, 49 / 2 };
    float angle = 0.0f;


    void init() override{

        player = &entity->getComponent<PositionComponent>();

        srcR.x  = 0;
        srcR.y  = 0;
        srcR.w = 360;
        srcR.h = 554;

        destRect.x = player->position.x - Game::camera.x;
        destRect.y = player->position.y + 32;
        destRect.w = 32;
        destRect.h = 49;

    }

    void draw() override{
        if (player->Is_skilling){
        SDL_RenderCopyEx(Game::renderer, texture, &srcR, &destRect, angle, &center, SDL_FLIP_NONE);
        }

    }

    void update() override{

        if (player->Is_skilling){
            texture =  IMG_LoadTexture(Game::renderer, "image/molotov.png");
            angle += 1.0f;

    }
        else{
            SDL_DestroyTexture(texture);
        }
    }
};

#endif // SKILL_H_INCLUDED
