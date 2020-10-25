#pragma once
#include "alignment.h"

/**
 * contains methods to attach alignments to the camera, as well as the camera x and y offsets
 */
namespace camera {
    extern int x, y, x_raw, y_raw;
    void bind(Alignment* a);
    void unbind(Alignment* a);
}

/**
 * INTENRAL USE ONLY
 * methods for engine internal uses of camera updates
 */
namespace camera_i {

    void update();
}