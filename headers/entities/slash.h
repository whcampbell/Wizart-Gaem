#pragma once
#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class AttackSlash : public  Entity {
private:
    int ticks;
    Sprite* activeSprite;
public:
    AttackSlash();
    void update();
    void render();
    ~AttackSlash();
};