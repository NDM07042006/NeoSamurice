#include "Collision.h"
bool Collision::AABB(const SDL_Rect& RectA,const SDL_Rect& RectB){
    if (RectA.x + RectA.w >= RectB.x &&
        RectB.x + RectB.w >= RectA.x &&
        RectA.y + RectA.h >= RectB.y &&
        RectB.y + RectB.h >= RectA.y ){
            return true;
        }
    else{
        return false;
    }
}




