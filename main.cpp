
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>
#define window_width 800
#define window_height 600
#define fps 24
#include "game.h"
#include <SDL_mixer.h>



using namespace std;
void framerate(Uint32 starting_tick){
    if ((100/fps) > SDL_GetTicks() - starting_tick){
        SDL_Delay(100/ fps - (SDL_GetTicks() - starting_tick));
    }
}




Game *game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();
    game->init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, false);



    while (game->running()) {
        Uint32 starting_tick = SDL_GetTicks();
        game->handleEvent();
        game->update();
        game->render();
        framerate(starting_tick);
    }


    game->clean();

    return 0;
}

