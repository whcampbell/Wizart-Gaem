#pragma once
#include "scene.h"

namespace scene {
    class Test : public Scene {
    public:
        void init();
        void update();
        void render();
    };
}