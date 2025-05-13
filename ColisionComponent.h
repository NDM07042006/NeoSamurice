
#ifndef COLISIONCOMPONENT_H_INCLUDED
#define COLISIONCOMPONENT_H_INCLUDED
#include <SDL.h>
#include <string>
class CollisionComponent: public Component{
public:
    SDL_Rect collider;
    std::string tag;

    PositionComponent* Transform;
    CollisionComponent(std::string s){
        tag = s;
    }

    void init() override {
        if (!entity->hasComponent<PositionComponent>()){
            entity->addComponent<PositionComponent>();
        }
        Transform = &entity->getComponent<PositionComponent>();
    }

    void update()override{
        collider.x = static_cast<int>(Transform->position.x);
        collider.y = static_cast<int>(Transform->position.y);

        collider.w = Transform->width * Transform->scale;
        collider.h = Transform->height * Transform->scale;
    }

};


#endif // COLISIONCOMPONENT_H_INCLUDED
