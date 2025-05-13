
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include "game.h"
#include <SDL.h>
class GameObject{

public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();
    void Update();
    void Render();


    int xpos;
    int ypos;

    SDL_Texture* objectTexture;
    SDL_Rect srcRect, desRect;




};

#endif // GAMEOBJECT_H_INCLUDED
