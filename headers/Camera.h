#pragma once
#include "Alignment.h"

namespace camera {
    int x();
    int y();
    void bind(Alignment* a);
    void unbind(Alignment* a);
}

namespace camera_i {
    void update();
}