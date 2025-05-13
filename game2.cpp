#include "game.h"
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "Component.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Collision.h"
#include "FontGame.h"
#include "Button.h"
#include <vector>
#include <SDL_mixer.h>
bool test = true;
int testtime = 500;

std::vector<Entity*> enemies;
std::vector<Entity*> objective ;

std::vector<Entity*> PlayerArr ;

bool justBeginTheGame = false;
bool finishTheWave = true;
Manager manager;
int waitTime = 500;
enum groupLabel : std::size_t
{
    groupMap,
    groupPlayer,
    groupEnemies
};

int wave = 1;


void Game::despawnEntity(Entity* entity, std::vector<Entity*>& container) {
    if (entity) {
        entity->destroy();
        container.erase(std::remove(container.begin(), container.end(), entity), container.end());
    }
    manager.refresh();
}
void Game::despawnAll(std::vector<Entity*>& container) {
    int number = container.size();
    for (int t = 0; t < number; t++) {
        container[t]->destroy();
    }
    manager.refresh();
    container.clear();
}





Map* map;

enum GameState {
    MENU,
    PLAYING,
    OPTION,
    GAMEOVER,
    PAUSEMENU

};

GameState currentState = MENU;




SDL_Event Game::event;






SDL_Renderer* Game::renderer = nullptr;
Button* startButton = nullptr;
Button* optionButton = nullptr;
Button* playagain = nullptr;
Button* sound = nullptr;
Button* resume = nullptr;
Button* mainmenu = nullptr;
Button* quitGame = nullptr;
TTF_Font* font = nullptr;


SDL_Rect Game::camera = {0, 0, 800, 600};

Game::Game(){}

Game::~Game(){}
SDL_Rect bgRect = {0, 0, 800, 600};
SDL_Texture* bgTexture;
SDL_Texture* house;
SDL_Rect hRect = {400-16*3, 600 - 32 * 4 - 20, 32*3, 32*3};

void Game::startNewGame() {

    auto& player(manager.addEntity());
    player.addComponent<PositionComponent>(400, 600 - 32 * 5 - 20);
    player.addComponent<SpriteComponent>("image/PlayerIdle.png", 4, 5, 200);
    player.addComponent<KeyboardControler>();
    player.addComponent<CollisionComponent>("player");
    player.addComponent<HitBox>("player");
    player.addGroup(groupPlayer);
    player.addComponent<GameStat>(100, 50);
    player.addComponent<PlayerHealthBar>();
    player.addComponent<Skill>();
    PlayerArr.push_back(&player);





    camera.x = 0;
    camera.y = 0;
}


void Game::spawnEnemy() {
    auto& leftty(manager.addEntity());
    auto& rightty(manager.addEntity());
    leftty.addComponent<PositionComponent>(-350, 600-32*5-20);
    leftty.addComponent<SpriteComponent>("image/EnemyWarriorIdle.png", 3, 4, 100);
    leftty.addComponent<EnemyBehavior>();
    leftty.addComponent<CollisionComponent>("nothing");
    leftty.addGroup(groupEnemies);
    leftty.addComponent<GameStat>(100, 10);
    leftty.addComponent<HealthBar>();
    leftty.addComponent<HitBox>("leftty");
    leftty.getComponent<HitBox>().setHitBox(32, 32);
    leftty.getComponent<EnemyBehavior>().movingSpeed = 0.5;

    rightty.addComponent<PositionComponent>(1150, 600-32*5-20);
    rightty.addComponent<SpriteComponent>("image/EnemyWarriorIdle_Flip.png", 3, 4, 100);
    rightty.addComponent<EnemyBehavior>();
    rightty.addComponent<CollisionComponent>("nothing");
    rightty.addGroup(groupEnemies);
    rightty.addComponent<GameStat>(100, 10);
    rightty.addComponent<HealthBar>();
    rightty.getComponent<EnemyBehavior>().movingSpeed = 0.5;
    rightty.addComponent<HitBox>("rightty");
    rightty.getComponent<HitBox>().setHitBox(32, 32);

    enemies.push_back(&leftty);
    enemies.push_back(&rightty);

}

void Game::spawnObjective() {
    auto& leftty(manager.addEntity());
    std::cout << "Adding leftty\n";

    auto& rightty(manager.addEntity());


    leftty.addComponent<PositionComponent>(-350, 600 - 32 * 5 - 20);
    leftty.addComponent<SpriteComponent>("image/FlameDemon Evolved.png", 3);
    leftty.addComponent<EnemyBehavior>();
    leftty.addComponent<CollisionComponent>("leftty");
    leftty.addGroup(groupEnemies);
    leftty.addComponent<GameStat>(500, 10);
    leftty.addComponent<HealthBar>();
    leftty.getComponent<EnemyBehavior>().movingSpeed = 0.1;

    std::cout << "doing fin1\n";


    rightty.addComponent<PositionComponent>(1150, 600 - 32 * 5 - 20);
    rightty.addComponent<SpriteComponent>("image/FlameDemon Evolved_Flip.png", 3);
    rightty.addComponent<EnemyBehavior>();
    rightty.addComponent<CollisionComponent>("rightty");
    rightty.addGroup(groupEnemies);
    rightty.addComponent<GameStat>(500, 10);
    rightty.addComponent<HealthBar>();
    rightty.getComponent<EnemyBehavior>().movingSpeed = 0.1;
    std::cout << "doing fin2\n";


    objective.push_back(&leftty);
    objective.push_back(&rightty);
    std::cout << "doing fin3\n";

}

void Game::startNextWave() {


    spawnObjective();
}


void Game::init(const char* title, int xpos, int ypos, int width, int length, bool fullscreen){
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (!(TTF_Init() == 0)){
        std::cout << TTF_GetError();
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, length, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "render created" << std::endl;
        }
        Is_running = true;
    }else{
        Is_running = false;
    }

    map = new Map();



    font = TTF_OpenFont("font/ShortBaby.ttf", 30);
    startButton = new Button(renderer, font, "New Game", 300, 200, 200, 60);
    optionButton = new Button(renderer, font, "Option", 300, 300, 200, 60);
    sound = new Button(renderer, font, "Sound: ON", 300, 400, 200, 60);
    resume = new Button(renderer, font, "Resume", 300, 200, 200, 60);
    playagain = new Button(renderer, font, "New Game", 300, 300, 200, 60);
    mainmenu = new Button(renderer, font, "Main Menu", 300, 400, 200, 60);
    quitGame = new Button(renderer, font, "Quit", 300, 500, 200, 60);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("SDL_mixer initialization failed: %s\n", Mix_GetError());
    }

    bgm = Mix_LoadMUS("sound/backgroundMusic.mp3");
    if (!bgm) {
        SDL_Log("Failed to load background music: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgm, -1);
    }
    Mix_VolumeMusic(0);



    bgTexture = TextureManager::Load_texture("image/background.png");
    house = TextureManager::Load_texture("image/house.png");


}


void Game::update(){

    if (currentState == PLAYING){
    std::size_t counter = manager.getEntityCount();
    std::cout << counter << std::endl;

    if (justBeginTheGame){
        manager.refresh();
        if (!enemies.empty()){
        despawnAll(enemies);}


        if (!objective.empty()){
        despawnAll(objective);}

        if (!PlayerArr.empty()){

            PlayerArr[0]->destroy();

            manager.refresh();

            PlayerArr.clear();

        }


        if (map) {
            delete map;
            map = nullptr;
        }
        map = new Map();

        startNewGame();
        PlayerArr[0]->getComponent<HitBox>().setHitBox(90, 32);
        std::cout << PlayerArr.size() << std::endl;

        justBeginTheGame = false;

    }



    int PlayerXpos;

    for (auto& p : PlayerArr){
    PlayerXpos = p->getComponent<PositionComponent>().x();}







    if (enemies.empty() && objective.empty() && finishTheWave){
        waitTime = 500;
        finishTheWave =- false;

    }

    if (waitTime >= 0){
        waitTime --;
    }




    auto isDead = [](Entity* e) { return !e || !e->IsActive(); };
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), isDead), enemies.end());
    objective.erase(std::remove_if(objective.begin(), objective.end(), isDead), objective.end());

    manager.refresh();


if (!waveTransitioning && enemies.empty() && objective.empty() && waitTime <= 0) {
    waveTransitioning = true;

    std::cout << "Transitioning to next wave...\n";







    if (wave >= 2) {
        wave = 2;
    }


    startNextWave();






    waveTransitioning = false;
    finishTheWave = true;
    waitTime = 500;


}







    for (auto& enemy : enemies){
        if (enemy->hasComponent<EnemyBehavior>()) {
            enemy->getComponent<EnemyBehavior>().PlayerXpos = PlayerXpos;
}

        if (enemy->getComponent<PositionComponent>().side_faccing == -1 &&
        enemy->getComponent<PositionComponent>().Is_walking == 0){
        enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorIdle.png");
        enemy->getComponent<SpriteComponent>().setFrame(4);

    }
     if (enemy->getComponent<PositionComponent>().side_faccing == 1 &&
        enemy->getComponent<PositionComponent>().Is_walking == 0 ){
        enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorIdle_Flip.png");
        enemy->getComponent<SpriteComponent>().setFrame(4);
    }
    if (enemy->getComponent<PositionComponent>().side_faccing == 1 &&
        enemy->getComponent<PositionComponent>().Is_walking){
           enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorWalk_Flip.png");
           enemy->getComponent<SpriteComponent>().setFrame(6);
        }
    if (enemy->getComponent<PositionComponent>().side_faccing == -1 &&
        enemy->getComponent<PositionComponent>().Is_walking){
           enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorWalk.png");
           enemy->getComponent<SpriteComponent>().setFrame(6);
        }
    if (enemy->getComponent<PositionComponent>().side_faccing == -1 &&
        enemy->getComponent<PositionComponent>().Is_attacking){
            enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorAttack.png");
           enemy->getComponent<SpriteComponent>().setFrame(3);
           enemy->getComponent<SpriteComponent>().setSpeed(200);
        }

    if (enemy->getComponent<PositionComponent>().side_faccing == 1 &&
        enemy->getComponent<PositionComponent>().Is_attacking){
            enemy->getComponent<SpriteComponent>().setTex("image/EnemyWarriorAttack_Flip.png");
           enemy->getComponent<SpriteComponent>().setFrame(3);
           enemy->getComponent<SpriteComponent>().setSpeed(200);

        }

    }

    for (auto& enemy: enemies){
    if (enemy->getComponent<PositionComponent>().Is_attacking){
    for (auto& p : PlayerArr){
        if (Collision::AABB(enemy->getComponent<HitBox>().hitbox,
                            p->getComponent<CollisionComponent>().collider)){
            if (enemy->getComponent<PositionComponent>().dealDamage){
                p->getComponent<GameStat>().takeDamage(
                    enemy->getComponent<GameStat>().attackDamage);
                }
            }
        }

    }
    }

    for (auto& p: PlayerArr){
    if (p->getComponent<PositionComponent>().Is_attacking) {
    for (auto& enemy : enemies) {
        if (!enemy) continue;

        if (Collision::AABB(p->getComponent<HitBox>().hitbox,
                            enemy->getComponent<CollisionComponent>().collider)) {

            if (p->getComponent<PositionComponent>().dealDamage) {
                enemy->getComponent<GameStat>().takeDamage(
                    p->getComponent<GameStat>().attackDamage);
            }

        }
    }
}
}

    for (auto& enemy : objective){
        if (enemy->hasComponent<EnemyBehavior>()) {
            enemy->getComponent<EnemyBehavior>().PlayerXpos = 400;
}


    }

    for (auto& e : enemies) {
    if (e->hasComponent<EnemyBehavior>() && e->getComponent<GameStat>().isDead()) {
        despawnEntity(e, enemies);
}


}
    for (auto& e : objective) {
    if (e->hasComponent<EnemyBehavior>() && e->getComponent<GameStat>().isDead()) {
        despawnEntity(e, objective);
}

}


    manager.update();




    for (auto& p : PlayerArr){

    if (p->getComponent<PositionComponent>().side_faccing == -1 &&
        p->getComponent<PositionComponent>().Is_walking == 0){
        p->getComponent<SpriteComponent>().setTex("image/PlayerIdle_Flip.png");
        p->getComponent<SpriteComponent>().setFrame(5);

    }
     if (p->getComponent<PositionComponent>().side_faccing == 1 &&
             p->getComponent<PositionComponent>().Is_walking == 0){
        p->getComponent<SpriteComponent>().setTex("image/PlayerIdle.png");
        p->getComponent<SpriteComponent>().setFrame(5);
    }

     if (p->getComponent<PositionComponent>().side_faccing == -1 &&
             p->getComponent<PositionComponent>().Is_walking == -1){
        p->getComponent<SpriteComponent>().setTex("image/PlayerRun_Flip.png");
        p->getComponent<SpriteComponent>().setFrame(7);
    }
    if (p->getComponent<PositionComponent>().side_faccing == 1 &&
             p->getComponent<PositionComponent>().Is_walking == 1){
        p->getComponent<SpriteComponent>().setTex("image/PlayerRun.png");
        p->getComponent<SpriteComponent>().setFrame(7);
    }
    if (p->getComponent<PositionComponent>().side_faccing == 1 &&
        p->getComponent<PositionComponent>().Is_jumping == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerJump.png");
        p->getComponent<SpriteComponent>().setFrame(11);
        p->getComponent<SpriteComponent>().setSpeed(130);
    }
    if (p->getComponent<PositionComponent>().side_faccing == -1 &&
        p->getComponent<PositionComponent>().Is_jumping == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerJump_Flip.png");
        p->getComponent<SpriteComponent>().setFrame(11);
        p->getComponent<SpriteComponent>().setSpeed(130);
    }

    if (p->getComponent<PositionComponent>().side_faccing == -1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo1 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack1_Flip.png");
        p->getComponent<SpriteComponent>().setSpeed(100);
        p->getComponent<SpriteComponent>().setFrame(5);
        }
    if (p->getComponent<PositionComponent>().side_faccing == 1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo1 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack1.png");
        p->getComponent<SpriteComponent>().setSpeed(100);
        p->getComponent<SpriteComponent>().setFrame(5);
        }

    if (p->getComponent<PositionComponent>().side_faccing == -1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo2 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack2_Flip.png");
        p->getComponent<SpriteComponent>().setSpeed(150);
        p->getComponent<SpriteComponent>().setFrame(3);
        }
    if (p->getComponent<PositionComponent>().side_faccing == 1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo2 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack2.png");
        p->getComponent<SpriteComponent>().setSpeed(150);
        p->getComponent<SpriteComponent>().setFrame(3);
        }

    if (p->getComponent<PositionComponent>().side_faccing == -1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo3 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack3_Flip.png");
        p->getComponent<SpriteComponent>().setSpeed(300);
        p->getComponent<SpriteComponent>().setFrame(2);
        }
    if (p->getComponent<PositionComponent>().side_faccing == 1 &&
        p->getComponent<PositionComponent>().Is_attacking == true &&
        p->getComponent<PositionComponent>().attackCombo3 == true){
        p->getComponent<SpriteComponent>().setTex("image/PlayerAttack3.png");
        p->getComponent<SpriteComponent>().setSpeed(300);
        p->getComponent<SpriteComponent>().setFrame(2);
        }




    if (p->getComponent<PositionComponent>().position.x <= -430){
        p->getComponent<PositionComponent>().position.x += 1;
    }
    if (p->getComponent<PositionComponent>().position.x >= 1100){
        p->getComponent<PositionComponent>().position.x += -1;
    }





    camera.x = p->getComponent<PositionComponent>().position.x  - 350;

    if (camera.x < -400){
        camera.x = -400;
    }


    if (camera.x > 400){
        camera.x = 400;
    }
    camera.y = 0;





    }



    for (auto& p: PlayerArr){
    if (p->getComponent<PositionComponent>().Is_attacking) {
    for (auto& enemy : enemies) {
        if (!enemy) continue;

        if (Collision::AABB(p->getComponent<HitBox>().hitbox,
                            enemy->getComponent<CollisionComponent>().collider)) {

            if (p->getComponent<PositionComponent>().dealDamage) {
                enemy->getComponent<GameStat>().takeDamage(
                    p->getComponent<GameStat>().attackDamage);
            }

        }
    }
}
}
    for (auto& p: PlayerArr){
        if (p->getComponent<PositionComponent>().Is_skilling){

        }
    }

    for (auto& enemy: objective){
        for (auto& p : PlayerArr){
            if (Collision::AABB(p->getComponent<HitBox>().hitbox,
                             enemy->getComponent<CollisionComponent>().collider)){
                if (p->getComponent<PositionComponent>().dealDamage) {
                    enemy->getComponent<GameStat>().takeDamage(p->getComponent<GameStat>().attackDamage);
            }

        }
    }
    }
    for (auto& p: PlayerArr){
    if (p->getComponent<GameStat>().isDead()){
        currentState = GAMEOVER;
    }
    }

    hRect.x = 400-16*3 - camera.x;
    }

}












void Game::render() {
    SDL_RenderClear(renderer);

    if (currentState == MENU) {
        startButton->render();
        optionButton->render();
        sound->render();
        quitGame->render();
    }
    if (currentState == PLAYING) {
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);
        SDL_RenderCopy(renderer, house, nullptr, &hRect);


        map->DrawMap();

        auto& enemiesGroup = manager.getGroup(groupEnemies);
        auto& playersGroup = manager.getGroup(groupPlayer);

        for (auto& t : enemiesGroup) {
            t->draw();
        }
        for (auto& t : playersGroup) {
            t->draw();
        }

    }


    if (currentState == GAMEOVER){
        startButton->render();
    }

    if (currentState == PAUSEMENU){
        resume->render();
        playagain->render();
        mainmenu->render();

    }


    SDL_RenderPresent(renderer);
}


void Game::clean() {
    delete map;

    delete startButton;
    delete optionButton;
    delete playagain;
    delete sound;
    delete resume;

    despawnAll(enemies);
    despawnAll(objective);



    if (!PlayerArr.empty()){
        PlayerArr[0]->destroy();
        manager.refresh();


    }
    PlayerArr.clear();





    if (bgTexture) {
        SDL_DestroyTexture(bgTexture);
        bgTexture = nullptr;
    }

    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    Mix_FreeMusic(bgm);
    Mix_CloseAudio();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

void Game::handleEvent() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Is_running = false;
            return;
        }

        switch (currentState) {
            case MENU: {
                bool startClicked  = startButton  && startButton->handleEvent(&event);
                bool optionClicked = optionButton && optionButton->handleEvent(&event);
                bool soundClicked  = sound        && sound->handleEvent(&event);
                bool quitClicked   = quitGame     && quitGame->handleEvent(&event);

                if (startClicked) {
                    std::cout << "Start Clicked!" << std::endl;
                    justBeginTheGame = true;
                    currentState = PLAYING;
                }

                if (optionClicked) {
                    std::cout << "Option Clicked!" << std::endl;
                }

                if (soundClicked) {
                    if (alternate) {
                        sound->setText("Sound: ON");
                        Mix_VolumeMusic(128);
                    } else {
                        sound->setText("Sound: OFF");
                        Mix_VolumeMusic(0);
                    }
                    alternate = !alternate;
                }

                if (quitClicked) {
                    Is_running = false;
                }
                break;
            }

            case GAMEOVER: {
                bool startClicked = startButton && startButton->handleEvent(&event);
                if (startClicked) {
                    justBeginTheGame = false;
                    currentState = PLAYING;
                }
                break;
            }

            case PLAYING: {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
                    currentState = PAUSEMENU;
                }
                break;
            }

            case PAUSEMENU: {
                bool resumeClicked   = resume    && resume->handleEvent(&event);
                bool playAgainClicked = playagain && playagain->handleEvent(&event);
                bool menuClicked     = mainmenu && mainmenu->handleEvent(&event);

                if (resumeClicked) {
                    currentState = PLAYING;
                } else if (playAgainClicked) {
                    justBeginTheGame = false;
                    currentState = PLAYING;
                } else if (menuClicked) {
                    currentState = MENU;
                }
                break;
            }

            default:
                break;
        }
    }
}
