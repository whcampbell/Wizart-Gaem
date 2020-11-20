#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Skeleton : public Entity {
    private :
        Sprite* run;
        Sprite* hurt;

        Sprite* activeSprite;
        enum animstates {
            anim_run, anim_hurt, ANIM_MAX
        };
        StateMachine<ANIM_MAX> animator;
        void move();
    public :
        Skeleton();
        void update();
        void render();
        ~Skeleton();
};