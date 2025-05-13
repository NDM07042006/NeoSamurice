
#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED
#include "game.h"
#include "EntityComponentSystem.h"
#include "Component.h"

class KeyboardControler: public Component{
public:
    int noInputFrame = 0;
    PositionComponent *input;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    bool wasPressed = false;
    bool isPressed;
    void init() override{
        input = &entity->getComponent<PositionComponent>();
    }

    void update() override {
		input->velocity.x = 0;




		if (keystates[SDL_SCANCODE_A] && !input->Is_attacking) {
			input->velocity.x = -1;
			input->side_faccing = -1;
			input->Is_walking = -1;
		}

		if (keystates[SDL_SCANCODE_D] && !input->Is_attacking) {
			input->velocity.x = 1;
			input->side_faccing = 1;
			input->Is_walking = 1;

		}
        isPressed = keystates[SDL_SCANCODE_SPACE];
		if (isPressed && !wasPressed){
            if (!input->Is_jumping){
                input->Is_jumping = true;
                input->velocity.y = input->jumpPower;
            }
		}
		wasPressed = isPressed;


        if (keystates[SDL_SCANCODE_K]) {
            if (!input->Is_dashing && input->dashCooldown <= 0) {
                input->Is_dashing = true;
                input->dashTimer = input->maxDashTime;
                input->dashCooldown = input->maxDashCooldown;

                if (input->side_faccing == -1){
                    input->dashDirection = -1;}
                else if (input->side_faccing == 1){
                    input->dashDirection = 1;}

            }
        }
        if (noInputFrame >= 0){
            noInputFrame --;
        }
        if (keystates[SDL_SCANCODE_J] && noInputFrame <= 0){
            if (!input->Is_attacking && input->attackTimer <= 0){

                input->Is_attacking = true;
                input->attackTimer = input->maxAttacktimer;
                input->attackCombo1 = true;
                input->attackCombo2 = false;
                input->attackCombo3 = false;

            }

            else if  (input->Is_attacking && input->attackTimer <= 30 && input->attackTimer >= 2 && input->attackCombo1){
                input->Is_attacking = true;
                input->attackTimer = input->maxAttacktimer;
                input->attackCombo1 = false;
                input->attackCombo2 = true;
                input->attackCombo3 = false;


            }
            else if (input->Is_attacking && input->attackTimer <= 30 && input->attackTimer >= 2 && input->attackCombo2){
                input->Is_attacking = true;
                input->attackTimer = input->maxAttacktimer;
                input->attackCombo1 = false;
                input->attackCombo2 = false;
                input->attackCombo3 = true;
                noInputFrame = 200;

            }
        }

        if (keystates[SDL_SCANCODE_U] && input->SkillCoolDown <= 0){
            input->Is_skilling = true;
            input->SkillCoolDown = input->MaxSkillCoolDown;
        }



        }
    }



;




#endif // KEYBOARD_H_INCLUDED
