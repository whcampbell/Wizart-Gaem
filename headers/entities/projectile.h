#pragma once
#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class AttackProjectile : public  Entity {
private:
    int ticks;
    Sprite* activeSprite;
public:
    AttackProjectile();
    void update();
    void render();
    ~AttackProjectile();
};