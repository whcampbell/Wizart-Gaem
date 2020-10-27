#pragma once

#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Crate : public Entity {
private:
    Sprite* activeSprite;
public:
    Crate();
    void update();
    void render();
    ~Crate();
};