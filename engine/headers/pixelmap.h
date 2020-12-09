#pragma once
#include "render.h"
#include "globals.h"
#include "alignment.h"

class PixelMap {
private:
    int w, h, c = 4;
    char* pixels;
public:

    PixelMap(int w, int h) : w(w), h(h) {
        pixels = new char[w * h * c];
    }

    int& operator[](int index) {
        return *((int*)(pixels + index));
    }

    int& operator()(int x, int y) {
        return *((int*)(pixels + y*w + x));
    }

    ~PixelMap() {
        delete[] pixels;
    }
};

class PixelRenderer : Renderable {
private:

public:
    /**
     * Draws the given pixel array at the specified x and y coordinates,
     * with the given z sorting
     * 
     * int x    -   x position to draw at
     * int y    -   y position to draw at
     * int z    -   z layer for sorting
     */ 
    void render(int x, int y, int z, float scale = GAME_SCALE);

    /**
     * Draws the given pixel array using the information contained in
     * an alignment, with the given z sorting
     * 
     * Alignment* align -   a pointer to the alignment to reference
     * int z            -   z layer for sorting
     */ 
    void render(Alignment* align, int z, float scale = GAME_SCALE);

    /**
     * Draws the given pixel array using the information contained in
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
    void render(Alignment* align, int xoff, int yoff, int z, float scale = GAME_SCALE);


};

namespace render {
    void drawPixels(PixelMap map, int x, int y, int z);
};

