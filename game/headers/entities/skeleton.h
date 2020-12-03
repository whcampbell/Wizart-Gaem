#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Skeleton : public Entity {
    private :
        Sprite* activeSprite;
        enum animstates {
            anim_run, ANIM_MAX
        };
        Sprite** sprites = new Sprite*[ANIM_MAX]{new Sprite("skelly_run")};
        StateMachine<ANIM_MAX, Sprite*> animator;
        void move();
    public :
        Skeleton();
        void update();
        void render();
        ~Skeleton();
};