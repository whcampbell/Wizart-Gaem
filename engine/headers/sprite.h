#pragma once
#include "alignment.h"
#include <string>
#include <internal/renderable.h>

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
    virtual void render(int x, int y, int z) = 0;

    /**
     * Draws the given renderable using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    virtual void render(Alignment* align, int z) = 0;

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
    virtual void render(Alignment* align, int xoff, int yoff, int z) = 0;

    virtual ~Renderable() = 0;
};

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
    void render(int x, int y, int z);

    /**
     * Draws the given sprite using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int z);

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
    void render(Alignment* align, int xoff, int yoff, int z);

    /**
     * Draws a part of the given sprite at the specified x and y
     * coordinates starting at the top left, with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int w    -   starting at the sprite's top left corner, how
     *              far to draw in the x direction
     * int h    -   starting at the sprite's top left corner, how
     *              far to draw in the y direction
     * int z    -   z layer for sorting
     */ 
    void render(int x, int y, int w, int h, int z);

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
    void render(int x, int y, int x0, int y0, int w, int h, int z);

    /**
     * sets the current frame for this sprite
     * 
     * int f    -   the frame to set this sprite to
     */ 
    void setFrame(int f);
};

struct Text : public Renderable {
private:
    int w, h;
    std::string text;
    int size;
    SDL_Color color;
    bool u_flag = false;
    SDL_Texture* texture = nullptr;
    void refresh();
public:

    /**
     * initializes a renderable which draws text to the screen
     * 
     * string text      -   the text to draw
     * int size         -   the font size for the text
     * SDL_Color color  -   the {r, g, b} color of the text
     */ 
    Text(std::string text, int size, SDL_Color color);

    ~Text();

    /**
     * updates the text for this renderable. Calling this every frame
     * will have a strong performance impact and it should be avoided
     * 
     * string text  -   the new texxt
     */ 
    void update(std::string text);

    /**
     * updates the font size for this text. Calling this every frame
     * will have a strong performance impact and it should be avoided
     * 
     * int size  -   the font size for this text
     */ 
    void update(int size);

    /**
     * updates the color which this text should be drawn as. Calling
     * this every frame will have a strong performance impact and it
     * should be avoided
     * 
     * SDL_Color color  -   the {r, g, b} color to draw the text as
     */ 
    void update(SDL_Color color);

     /**
     * Draws the given text at the specified x and y coordinates,
     * with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int z    -   z layer for sorting
     */ 
    void render(int x, int y, int z);

    /**
     * Draws the given text using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int z);

    /**
     * Draws the given text using the information contained in
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
    void render(Alignment* align, int xoff, int yoff, int z);
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