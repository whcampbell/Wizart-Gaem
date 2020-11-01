#pragma once
#include "alignment.h"

struct Hitbox
{
    int xoff = 0, yoff = 0;
    int w, h;
    Alignment* align;
};

namespace hitbox {
    bool collision(Hitbox* a1, Hitbox* a2);
}
 