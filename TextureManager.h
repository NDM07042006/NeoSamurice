
#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED


#include "game.h"
class TextureManager{
public:
    static SDL_Texture* Load_texture(const char* name);
    static void Draw(SDL_Texture* tex , SDL_Rect src, SDL_Rect dest);

}    ;
#endif // TEXTUREMANAGER_H_INCLUDED
