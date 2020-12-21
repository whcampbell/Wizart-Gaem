#pragma once
#include "alignment.h"

/**
 * contains methods to attach alignments to the camera, as well as the camera x and y offsets
 */
namespace camera {

    /**
     * x and y are camera offsets for rendering
     * x_adj and y_adj are camera offsets 
     * x_raw and y_raw are camera offsets not adjusted for gamescale and not
     * modified by the screen width/height
     */ 
    extern int x, y, x_raw, y_raw, x_adj, y_adj;

    /** 
     * Attaches an alignment to the camera. The camera will generate
     * an offset based on the average position of all attached alignments
     *
     * Alignment* a  -   the alignment to attach
     */
    void bind(Alignment* a);
    
    /**
     * Detatches an alignment from the camera. It will no longer be used in offset
     * calculations
     * 
     * Alignment* a - the alignment to detach
     */
    void unbind(Alignment* a);

    /**
     * Shakes the screen with a set intensity for a given duration
     * 
     * int intensity    -   the amount by which the screen is allowed
     *                      to expand beyond its normal bounds
     * int duration     -   how long the screen can shake for
     */ 
    void screenshake(int intensity, int duration);
}