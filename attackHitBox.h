#ifndef ATTACKHITBOX_H_INCLUDED
#define ATTACKHITBOX_H_INCLUDED

#include <SDL.h>
#include <string>

class HitBox : public Component {
public:
    SDL_Rect hitbox;
    std::string tag;
    PositionComponent* Transform;
    int widthHB;
    int heightHB;
    HitBox(std::string s) {
        tag = s;
        hitbox = {0, 0, 0, 0};
    }
    void setHitBox(int width, int height){
        widthHB = width;
        heightHB = height;
    }
    void init() override {
        if (!entity->hasComponent<PositionComponent>()) {
            entity->addComponent<PositionComponent>();
        }
        Transform = &entity->getComponent<PositionComponent>();
    }

    void update() override {
        if (Transform->Is_attacking) {
            if (Transform->side_faccing == 1) {
                hitbox.x = static_cast<int>(Transform->position.x + Transform->width * Transform->scale);
            } else {
                hitbox.x = static_cast<int>(Transform->position.x - 90);
            }


            hitbox.y = static_cast<int>(Transform->position.y + 70);
            hitbox.w = widthHB;
            hitbox.h = heightHB;



        } else {

            hitbox = {0, 0, 0, 0};
        }
        SDL_SetRenderDrawColor(Game::renderer, 100, 200, 0, 255);
        SDL_RenderFillRect(Game::renderer, &hitbox);

    }
};

#endif // ATTACKHITBOX_H_INCLUDED

