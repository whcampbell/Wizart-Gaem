#pragma once
#include "alignment.h"

struct Hitbox
{
    int xoff = 0, yoff = 0;
    int w, h;
    Alignment* align;


};

namespace hitbox {
    /**
     * checks if the input hitboxes overlap
     * 
     * Hitbox* a1   -   the first hitbox
     * Hitbox* a2   -   the second hitbox
     * returns      -   true if the hitboxes overlap, and false otherwise
     */ 
    bool collision(Hitbox* a1, Hitbox* a2);

    /**
     * draws an outline around the hitbox location
     */ 
    void render(Hitbox* h, int x, int y);

}
 