#include "eventpump.h"
#include "input.h" 

static int X = 0, Y = 0;

void mouse::move(SDL_MouseMotionEvent e) {
    X = e.x;
    Y = e.y;
}

int mouse::x() {
    return X;
}

int mouse::y() {
    return Y;
}
