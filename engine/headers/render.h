#pragma once
#include "SDL.h"

/**
 * struct representing every object that can be drawn to the screen
 */ 
struct Renderable {
public:

    /**
     * Draws the given renderable at the specified x and y coordinates,
     * with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int z    -   z layer for sorting
     */ 
    virtual void render(int x, int y, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y) = 0;

    /**
     * Draws the given renderable using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    virtual void render(Alignment* align, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y) = 0;

    /**
     * Draws the given renderable using the information contained in
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
    virtual void render(Alignment* align, int xoff, int yoff, int z, float scalex = GAMESCALE_X, float scaley = GAMESCALE_Y) = 0;

    virtual ~Renderable() = 0;
};

namespace render {

    /**
     * draws an unfilled rectangle
     * 
     * int x            -   x position to draw at (top left corner)
     * int y            -   y position to draw at (top left corner)
     * int w            -   width of the rectangle
     * int h            -   height of the rectangle
     * SDL_Color color  -   {r, g, b} color for the rectangle
     * int z            -   z layer for sorting
     */ 
    void drawRect(int x, int y, int w, int h, SDL_Color color, int z);

    /**
     * draws an filled rectangle
     * 
     * int x            -   x position to draw at (top left corner)
     * int y            -   y position to draw at (top left corner)
     * int w            -   width of the rectangle
     * int h            -   height of the rectangle
     * SDL_Color color  -   {r, g, b} color for the rectangle
     * int z            -   z layer for sorting
     */  
    void fillRect(int x, int y, int w, int h, SDL_Color color, int z);

    /**
     * draws a filled rectangle with a different colored outline
     * 
     * int x            -   x position to draw at (top left corner)
     * int y            -   y position to draw at (top left corner)
     * int w            -   width of the rectangle
     * int h            -   height of the rectangle
     * SDL_Color color1 -   {r, g, b} color for the rectangle fill
     * SDL_Color color2 -   {r, g, b} color for the rectangle outline
     * int z            -   z layer for sorting
     */ 
    void outlineRect(int x, int y, int w, int h, SDL_Color color1, SDL_Color color2, int z);
}