#pragma once
#include "component.h"
#include "vec.h"

struct Slots : public Component {
    int curr;
    Vector2 first;
    Vector2 second;
    Vector2 third;
};