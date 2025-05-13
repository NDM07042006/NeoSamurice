#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "EntityComponentSystem.h"
#include <SDL_mixer.h>

class Game{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int length, bool fullscreen);
    void handleEvent();
    void update();
    void render();
    void clean();


    bool running() {return Is_running;};

    static SDL_Renderer* renderer;
    static SDL_Event event;
     bool waveTransitioning = false;

    bool Is_running = false;
    bool on = false;
    static SDL_Rect camera;
    void spawnEnemy();
    void despawnEntity(Entity* entity, std::vector<Entity*>& container);
    void startNewGame();
    void pawnObjective();
    void spawnObjective();
    void despawnAll(std::vector<Entity*>& container);


    void startNextWave();

    std::vector<Entity*> enemies;
    std::vector<Entity*> objective;
    std::vector<Entity*> PlayerArr;




private:
    bool alternate = false;
    SDL_Window* window;
    int time = 0;
    Mix_Music* bgm = nullptr;




};


#endif // GAME_H_INCLUDED
