#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Player : public Entity {
private:
    Sprite* idle;
    Sprite* run;

    Sprite* hp_icon;
    Sprite* mp_icon;

    Sprite* activeSprite;
    int speed = 1;
    enum animstates {
    anim_idle, anim_run, ANIM_MAX  
    };
    StateMachine<ANIM_MAX> animator;
    void move_keyboard();
    void move_controller();
public:
    Player();
    void update();
    void render();
    ~Player();
};