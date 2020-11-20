#include "entities/skeleton.h"
#include "audio.h"
#include "camera.h"
#include "globals.h"
#include <iostream>
#include "fastmath.h"
#include "hitbox.h"

#include "components/hitpoints.h"
#include "components/movespeed.h"
#include "components/bufftimers.h"
#include "components/physics.h"


Skeleton::Skeleton() {
    run = new Sprite("skelly_run");
    // hurt = new Sprite("skeleton_hurt");

    *align->x_internal = 16;
    *align->y_internal = 16;
    activeSprite = run;
    align->pos.y = 100;
    align->pos.x = 0;

    Hitbox* box = registerHitbox("hurtbox");
    box->align = align;
    box->h = 16;
    box->w = 16;

    Hitpoints hp;
    hp.healthMax = 3;
    hp.health = hp.healthMax;
    *set<Hitpoints>() = hp;

    Movespeed move;
    move.speed = .4;
    *set<Movespeed>() = move;

    BuffTimers buff;
    buff.speedBoost = 0;
    *set<BuffTimers>() = buff;

    Physics physics;
    physics.velocity = {0,0};
    physics.acceleration = {0,0};
    physics.physicsActive = false;
    *set<Physics>() = physics;

}

void Skeleton::update() {
    activeSprite = run;
  
    if (!get<Physics>()->physicsActive) {
        float speed = get<Movespeed>()->speed;
        align->pos.x += speed;
    } else {
        Physics* physics = get<Physics>();
        align->pos.x += physics->velocity.x;
        align->pos.y += physics->velocity.y;
        physics->velocity.x += physics->acceleration.x;
        physics->velocity.y += physics->acceleration.y;
        if (abs(physics->velocity.x) - .1 <= 0 && abs(physics->velocity.y) - .1 <= 0) {
            physics->physicsActive = false;
            physics->acceleration.x = 0;
            physics->acceleration.y = 0;
        }
    }


}

void Skeleton::render() {
    activeSprite->render(align, camera::x, camera::y, 4);
}

Skeleton::~Skeleton() {
    delete(activeSprite);
}