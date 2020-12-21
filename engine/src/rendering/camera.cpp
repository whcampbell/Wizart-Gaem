#include "camera.h"
#include "internal/camera.h"
#include <vector>
#include <algorithm>
#include "globals.h"
#include <random>


static std::vector<Alignment*> targets;
static std::default_random_engine generator;
static std::uniform_int_distribution dir_distribution(-1, 1);
static int intensity = 0, timer = 0;

namespace camera {
    int x = 0, y = 0, x_raw = 0, y_raw = 0, x_adj = 0, y_adj = 0;
}


void camera::bind(Alignment* a) {
    targets.push_back(a);
}

void camera::unbind(Alignment* a) {
    targets.erase(std::remove(targets.begin(), targets.end(), a));
}

void camera::update() {
    int shakex = 0, shakey = 0;
    if (timer) {
        if (timer % 3) {
            shakex = dir_distribution(generator);
            shakey = dir_distribution(generator);
            shakex *= intensity;
            shakey *= intensity;
        }

        if (timer % 6) {
            intensity -= intensity / timer;
        }

        timer--;
        if (!timer)
            intensity = 0;
    }

    int dx = 0, dy = 0;

    if (targets.size()) {
        for (unsigned int i = 0; i < targets.size(); i++) {
            dx += targets[i]->pos.x;
            dy += targets[i]->pos.y;
        }

        dx /= targets.size();
        dy /= targets.size();
    }
    
    camera::x_raw += shakex + (dx - camera::x_raw) / 4;
    camera::y_raw += shakey + (dy - camera::y_raw) / 4;
    camera::x = camera::x_raw - GAME_WIDTH/2;
    camera::y = camera::y_raw - GAME_HEIGHT/2;
    camera::x_adj = camera::x_raw - SCREEN_WIDTH/2;
    camera::y_adj = camera::y_raw - SCREEN_HEIGHT/2;
}

void camera::screenshake(int strength, int duration) {
    if (strength > intensity)
        intensity = strength;
    if (duration > timer)
        timer = duration;
}