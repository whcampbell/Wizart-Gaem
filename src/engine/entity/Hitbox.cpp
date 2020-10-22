#include "Hitbox.h"

bool hitbox::collision(Hitbox* a1, Hitbox* a2) {
    if (a1->w < a2->w) {
        if (a1->align->pos.x > a2->align->pos.x + a2->w || a1->align->pos.x + a1->w < a2->align->pos.x)
            return false;        
    } else {
        if (a2->align->pos.x > a1->align->pos.x + a1->w || a2->align->pos.x + a2->w < a1->align->pos.x)
            return false;            
    }
    if (a1->h < a2->h) {
        if (a1->align->pos.y > a2->align->pos.y + a2->h || a1->align->pos.y + a1->h < a2->align->pos.y)
            return false;        
    } else {
        if (a2->align->pos.y > a1->align->pos.y + a1->h || a2->align->pos.y + a2->h < a1->align->pos.y)
            return false;
    }
    return true;
}

