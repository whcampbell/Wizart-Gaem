#pragma once
#include "Scene.h"

namespace hnd_i {
    void render();
    void update();
}

namespace hnd {
    void setScene(Scene* scene);

    void initScene(Scene* scene);
}