
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "game.h"

class Map{
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][50]);
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Texture* flower;


    int map[20][50];


};



#endif // MAP_H_INCLUDED
