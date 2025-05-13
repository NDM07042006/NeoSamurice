#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SDL.h>
class Collision{
public:
    static bool AABB(const SDL_Rect& RectA,const SDL_Rect& RectB);

};



#endif // COLLISION_H_INCLUDED
