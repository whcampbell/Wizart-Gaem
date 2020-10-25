#pragma once
#include "alignment.h"

struct Hitbox
{
    int w, h;
    Alignment* align;
};

namespace hitbox {
    bool collision(Hitbox* a1, Hitbox* a2);
}
 