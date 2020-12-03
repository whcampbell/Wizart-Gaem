#include "hitbox.h"
#include "sprite.h"
#include "internal/globals.h"

bool hitbox::collision(Hitbox* a1, Hitbox* a2) {
    if (!a1 || !a2)
        return false;
    int x1 = a1->align->pos.x - *(a1->align->x_internal) + a1->xoff;
    int x2 = a2->align->pos.x - *(a2->align->x_internal) + a2->xoff;
    int y1 = a1->align->pos.y - *(a1->align->y_internal) + a1->yoff;
    int y2 = a2->align->pos.y - *(a2->align->y_internal) + a2->yoff;

    if (a1->w < a2->w) {
        if (x1 > x2 + a2->w || x1 + a1->w < x2)
            return false;        
    } else {
        if (x2 > x1 + a1->w || x2 + a2->w < x1)
            return false;            
    }

    if (a1->h < a2->h) {
        if (y1 > y2 + a2->h || y1 + a1->h < y2)
            return false;        
    } else {
        if (y2 > y1 + a1->h || y2 + a2->h < y1)
            return false;
    }

    return true;
}

static SDL_Color color =  {255, 0, 255};
void hitbox::render(Hitbox* h, int xoff, int yoff) {
    render::drawRect(h->align->pos.x - *h->align->x_internal - xoff + h->xoff, h->align->pos.y - *h->align->y_internal - yoff + h->yoff, h->w, h->h, color, ENGINE_Z);
}
