#pragma once
#include "alignment.h"
#include "globals.h"
#include <string>
#include <internal/renderable.h>
#include "render.h"

struct Sprite : public Renderable {
private:
    Texture* texture;
	int frame;
    unsigned int anim_time;
public:
    unsigned int animDelta = 100;

    /**
     * initializes a sprite, lazyloading the requested texture if nescessary
     * 
     * string name  -   the name that the sprite has been registered under
     *                  (located in the sprite's metafile)
     */ 
    Sprite(std::string name);
 
     /**
     * Draws the given sprite at the specified x and y coordinates,
     * with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int z    -   z layer for sorting
     */ 
    void render(int x, int y, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y);

    /**
     * Draws the given sprite using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y);

    /**
     * Draws the given sprite using the information contained in
     * an alignment, subtracting the provided x and y offsets,
     * with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int xoff         -   an x offset which is subtracted from the
     *                      alignment x
     * int yoff         -   a y offset which is subtracted from the
     *                      alignment y
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int xoff, int yoff, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y);

    /**
     * Draws a part of the given sprite at the specified x and y
     * coordinates starting at a given position, with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int x0   -   x position relative to the sprite to draw from
     * int y0   -   y position relative to the sprite to draw from
     * int w    -   starting at the sprite's top left corner, how
     *              far to draw in the x direction
     * int h    -   starting at the sprite's top left corner, how
     *              far to draw in the y direction
     * int z    -   z layer for sorting
     */ 
    void render(int x, int y, int w, int h, int z, int x0 = 0, int y0 = 0, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y);

    /**
     * sets the current frame for this sprite
     * 
     * int f    -   the frame to set this sprite to
     */ 
    void setFrame(int f);
};