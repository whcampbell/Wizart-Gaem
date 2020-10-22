#include "Camera.h"
#include <vector>
#include <algorithm>

static int X = 0, Y = 0;
std::vector<Alignment*> targets;

int camera::x() {
    return X;
}

int camera::y() {
    return Y;
}

void camera::bind(Alignment* a) {
    targets.push_back(a);
}

void camera::unbind(Alignment* a) {
    targets.erase(std::remove(targets.begin(), targets.end(), a));
}

void camera_i::update() {
    int dx = 0, dy = 0;

    if (targets.size()) {
        for (unsigned int i = 0; i < targets.size(); i++) {
            dx += targets[i]->pos.x;
            dy += targets[i]->pos.y;
        }

        dx /= targets.size();
        dy /= targets.size();
    }

    X += dx;
    Y += dy;
}