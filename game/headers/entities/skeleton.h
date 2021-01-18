#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Skeleton : public Entity {
    private :
        Sprite* activeSprite;
        enum animstates {
            anim_run, anim_idle, anim_hurt, ANIM_MAX
        };
        Sprite** sprites = new Sprite*[ANIM_MAX]{new Sprite("skelly_run"), new Sprite("skelly_idle"), new Sprite("skelly_hurt")};
        StateMachine<ANIM_MAX, Sprite*> animator;
        void move();
    public :
        Skeleton();
        void update();
        void render();
        ~Skeleton();
};