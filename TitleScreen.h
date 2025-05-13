#ifndef TITLESCREEN_H_INCLUDED
#define TITLESCREEN_H_INCLUDED
#include <SDL.h>
#include "FontGame.h"
#include "pauseMenu.h"
#include "game.h"
#include <iostream>
#include <vector>


class gameMenu{
public:
    gameMenu();
    ~gameMenu();

    void render();
    void handleInput();
private:
    textBox text;
    SDL_Renderer* renderer;
    SDL_Texture* menuTex;



};

#endif // TITLESCREEN_H_INCLUDED
