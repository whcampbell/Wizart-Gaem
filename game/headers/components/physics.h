#pragma once

#include "component.h"
#include "vec.h"

struct Physics : public Component {
    Vector2 velocity;
    Vector2 acceleration;
    bool physicsActive;
};