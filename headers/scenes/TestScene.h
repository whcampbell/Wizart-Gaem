#pragma once
#include "Scene.h"
#include "Sprite.h"


namespace scene {
    class Test : public Scene {
    private:
        Sprite* sprite;
        Alignment align;
    public:
        void init();
        void update();
        void render();
    };
}