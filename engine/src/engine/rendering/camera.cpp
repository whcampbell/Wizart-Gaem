#include "camera.h"
#include <vector>
#include <algorithm>
#include "globals.h"

static std::vector<Alignment*> targets;
namespace camera {
    int x = 0, y = 0, x_raw = 0, y_raw = 0, x_adj = 0, y_adj = 0;
}
static int w = 1200, h = 675;

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
    
    camera::x_raw += (dx - camera::x_raw) / 4;
    camera::y_raw += (dy - camera::y_raw) / 4;
    camera::x = camera::x_raw - w/2/GAME_SCALE;
    camera::y = camera::y_raw - h/2/GAME_SCALE;
    camera::x_adj = camera::x_raw - w/2;
    camera::y_adj = camera::y_raw - h/2;
}