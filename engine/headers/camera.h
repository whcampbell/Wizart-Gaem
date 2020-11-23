#pragma once
#include "alignment.h"

/**
 * contains methods to attach alignments to the camera, as well as the camera x and y offsets
 */
namespace camera {
    extern int x, y, x_raw, y_raw, x_adj, y_adj;
    void bind(Alignment* a);
    void unbind(Alignment* a);
    void screenshake(int intensity, int duration);
}