#pragma once
#include "alignment.h"
#include "hitbox.h"



class Entity {
protected:
    Alignment align;
    Hitbox hitbox;
public:
    virtual void update() = 0;
    void tick();
    virtual void render() = 0;
    Alignment* pos();
    virtual ~Entity() = 0;
};