#include <cmath>
#include "fastmath.h"

float cos(int dx, int dy) {
    return dx / sqrt(dx * dx + dy * dy);
}

float sin(int dx, int dy) {
    return dy / sqrt(dx * dx + dy * dy);
}

int angle(int dx, int dy) {
    return (int)((atan2(dy, dx)) * 180 / PI + 360) % 360;
}