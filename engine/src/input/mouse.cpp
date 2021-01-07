#include "internal/eventpump.h"
#include "input.h" 
#include "globals.h"

static int X = 0, Y = 0;

void mouse::move(SDL_MouseMotionEvent e) {
    X = e.x;
    Y = e.y;
}

int mouse::x() {
    return X / GAMESCALE_X;
}

int mouse::y() {
    return Y / GAMESCALE_Y;
}

int mouse::x_adj() {
    return X;
}

int mouse::y_adj() {
    return Y;
}
