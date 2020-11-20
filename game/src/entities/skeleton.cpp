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

Skeleton::Skeleton() {
    run = new Sprite("skelly_run");
    // hurt = new Sprite("skeleton_hurt");

    *align->x_internal = 16;
    *align->y_internal = 16;
    activeSprite = run;
    align->pos.y = 100;
    align->pos.x = 0;

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

}

void Skeleton::update() {
    activeSprite = run;
    float speed = get<Movespeed>()->speed;
    align->pos.x += speed;
}

void Skeleton::render() {
    activeSprite->render(align, camera::x, camera::y, 4);
}

Skeleton::~Skeleton() {
    delete(activeSprite);
}