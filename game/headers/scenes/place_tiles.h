#pragma once
#include "scene.h"

namespace scene {
    class World : public Scene {
        
    public:
        void init();
        void update();
        void render();
    };
}