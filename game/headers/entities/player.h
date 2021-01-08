#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Player : public Entity {
private:
    Sprite* hp_icon;
    Sprite* mp_icon;
    Sprite* hp_back;
    Sprite* mp_back;
    Sprite* xp_icon;
    Sprite* xp_back;

    Sprite* activeSprite;
    enum animstates {
    anim_idle, anim_run, ANIM_MAX  
    };
    Sprite** sprites = new Sprite*[ANIM_MAX]{new Sprite("player1_idle"), new Sprite("player1_run")};
    StateMachine<ANIM_MAX, Sprite*> animator;
    void move_keyboard();
    void move_controller();
    void aoe_spell(int elm);
public:
    Player();
    void update();
    void render();
    ~Player();
};