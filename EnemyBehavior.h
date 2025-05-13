#ifndef ENEMYBEHAVIOR_H_INCLUDED
#define ENEMYBEHAVIOR_H_INCLUDED
#include "game.h"
#include "EntityComponentSystem.h"
#include "Component.h"
#include <math.h>

class EnemyBehavior: public Component{
public:
    int PlayerXpos;
    PositionComponent *enemy;
    int spawnXpos = 0;
    int TimeBeingActive = 500;
    const int MaxTimeBeingActive = 500;
    int RestTime = 0;
    int MaxRestTime = 100;
    float movingSpeed = 0;

    int attackCooldown = 0;
    bool noticed = false;
    bool Is_attacked = false;
    bool Is_resting = false;
    void init() override{

        enemy = &entity->getComponent<PositionComponent>();

    }

    void update(){
        if (!Is_resting) {

            TimeBeingActive--;
            if (TimeBeingActive <= 0) {
                Is_resting = true;
                RestTime = MaxRestTime;
            }


            if (enemy->position.x > PlayerXpos && Is_attacked == false) {
                enemy->side_faccing = 1;
                enemy->velocity.x = 0 - movingSpeed;
                enemy->Is_walking = true;
            } else if (enemy->position.x < PlayerXpos && Is_attacked == false) {
                enemy->side_faccing = -1;
                enemy->velocity.x = movingSpeed;
                enemy->Is_walking = true;
            }

            if (abs(enemy->position.x - PlayerXpos) <= 50) {
                enemy->velocity.x = 0;

            }

        } else {

            enemy->velocity.x = 0;
            RestTime--;
            if (RestTime <= 0) {
                Is_resting = false;
                TimeBeingActive = MaxTimeBeingActive;
            }
        }



        if (abs(enemy->position.x - PlayerXpos) <= 50 && attackCooldown <= 0){
            enemy->Is_attacking = true;
            enemy->attackTimer = enemy->maxAttacktimer;
            attackCooldown = 1000;
        }

        if (attackCooldown >= 0){
            attackCooldown --;
        }







    }

};


#endif // ENEMYBEHAVIOR_H_INCLUDED
