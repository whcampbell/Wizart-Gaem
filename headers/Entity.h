#pragma once
#include "Alignment.h"
#include "Hitbox.h"



class Entity {
protected:
    Alignment align;
    Hitbox hitbox;
public:
    virtual void update();
    void tick();
    virtual void render();
    Alignment* pos();
    virtual ~Entity();
};