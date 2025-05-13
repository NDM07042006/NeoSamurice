#ifndef PLAYERHEALTHBAR_H_INCLUDED
#define PLAYERHEALTHBAR_H_INCLUDED

#include <SDL.h>
#include "GameStat.h"
#include "PositionComponent.h"
#include "Component.h"
#include "game.h"

class PlayerHealthBar : public Component {
public:
    PositionComponent* transform;
    GameStat* stats;

    int barWidth = 200;
    int barHeight = 20;
    int offsetY = 32*4 + 20;

    void init() override {
        transform = &entity->getComponent<PositionComponent>();
        stats = &entity->getComponent<GameStat>();
    }

    void draw() override {
        float healthRatio = static_cast<float>(stats->health) / stats->maxHealth;

        SDL_Rect backRect = {
            50,
            50,
            barWidth,
            barHeight
        };

        SDL_Rect frontRect = {
            50,
            50,
            static_cast<int>(barWidth * healthRatio),
            barHeight
        };








        SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(Game::renderer, &backRect);


        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Game::renderer, &frontRect);

    }
};


#endif // PLAYERHEALTHBAR_H_INCLUDED
