#pragma once
#ifndef POSITIONCOMPONENT_H_INCLUDED
#define POSITIONCOMPONENT_H_INCLUDED
#include "Component.h"
#include "Vector2D.h"

class PositionComponent: public Component{
public:
    Vector2D position;
    Vector2D velocity;
    bool Is_jumping = false;
    const float gravity = 0.025;
    const float jumpPower = -2.0;

    float speed = 1;
    bool Is_dashing = false;
    int dashTimer = 0;
    const int maxDashTime = 15;
    float dashSpeed = 7.0f;
    int dashCooldown = 0;
    const int maxDashCooldown = 40;
    int dashDirection = 0;
    int side_faccing = 1;
    bool finishDashing = false;
    int Is_walking = 0;

    int height = 32;
    int width = 32;
    int scale  = 4;
    int counter = 0;
    bool Is_skilling = false;
    bool Is_attacking = false;
    int SkillCoolDown = 0;
    const int MaxSkillCoolDown = 700;


    int attackTimer = 0;
    const int maxAttacktimer = 100;
    bool attackCombo1 = false;
    bool attackCombo2 = false;
    bool attackCombo3 = false;
    bool dealDamage = false;

    SDL_Rect HitBoxRect;
    SDL_Color color = {255, 0, 0};

    PositionComponent(){
        position.zero();
    }

    PositionComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    PositionComponent(int sca){
        position.zero();
        scale = sca;
    }

    PositionComponent(float x, float y, int w, int h, int sca){
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sca;
    }

    void init() override {
        velocity.zero();

    }


    void update() override {


        Is_walking = 0;
        if (Is_dashing){
            position.x += velocity.x * speed* dashSpeed ;
        }else{
            position.x += velocity.x * speed;
            position.y += velocity.y ;}



        if (Is_jumping) {
            velocity.y += gravity;
            counter ++;
        }


        if (position.y >= 600-32*5-20) {
            position.y = 600-32*5-20;
            if (velocity.y >= 0 ) {
                Is_jumping = false;
                velocity.y = 0;
            }
        }

        if (Is_dashing){
            dashTimer --;

            if (dashTimer <= 0){
                Is_dashing = false;
                dashCooldown = maxDashCooldown;
                velocity.y = 0;


            }

            }
        else{
            if (dashCooldown > 0){
                dashCooldown --;
        }


    }
    if (Is_attacking){

        attackTimer--;

    }
    if (attackTimer == maxAttacktimer - 10){
        dealDamage = true;
    }
    else {
        dealDamage = false;
    }

    if (attackTimer <= 0){
        attackTimer = 0;
        Is_attacking = false;
        dealDamage = false;


        }

    if (SkillCoolDown >= 0){
        SkillCoolDown --;
        std::cout << SkillCoolDown << std::endl;
    }

    }




    float x(){
        return position.x;
    }
    float y(){
        return position.y;
    }

};




#endif // POSITIONCOMPONENT_H_INCLUDED

