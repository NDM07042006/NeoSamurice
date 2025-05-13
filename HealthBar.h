#ifndef HEALTHBAR_H_INCLUDED
#define HEALTHBAR_H_INCLUDED

#include <SDL.h>
#include "GameStat.h"
#include "PositionComponent.h"
#include "Component.h"
#include "game.h"

class HealthBar : public Component {
public:
    PositionComponent* transform;
    GameStat* stats;

    int barWidth = 50;
    int barHeight = 6;
    int offsetY = 32*4 + 20;

    void init() override {
        transform = &entity->getComponent<PositionComponent>();
        stats = &entity->getComponent<GameStat>();
    }

    void draw() override {
        float healthRatio = static_cast<float>(stats->health) / stats->maxHealth;

        SDL_Rect backRect = {
            static_cast<int>(transform->position.x + 32) - Game::camera.x,
            static_cast<int>(transform->position.y + offsetY),
            barWidth,
            barHeight
        };

        SDL_Rect frontRect = {
            static_cast<int>(transform->position.x + 32) - Game::camera.x,
            static_cast<int>(transform->position.y + offsetY),
            static_cast<int>(barWidth * healthRatio),
            barHeight
        };


        SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(Game::renderer, &backRect);


        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(Game::renderer, &frontRect);
    }
};

#endif // HEALTHBAR_H_INCLUDED
