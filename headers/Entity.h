#pragma once
#include "Alignment.h"



class Entity {
protected:
    Alignment align;
public:
    virtual void update();
    void tick();
    virtual void render();
    Alignment* pos();
    virtual ~Entity();
};