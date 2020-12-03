#include "tileset.h"

Tileset::Tileset(std::string name, int tilesize) {
    sprite = new Sprite(name);
    this->tilesize = tilesize;
}

void Tileset::render(int x, int y, Vector3 map) {
    sprite->render(x, y, map.x, map.y, tilesize, tilesize, map.z);
}

Tileset::~Tileset() {
    delete(sprite);
}


Vector3 tileset::defaultmap(int** arr, int x, int y, int w, int h) {
    short int m = 0;
    Vector3 off;
    int i = 11;
    for (int y0 = y - 1; y0 < y + 2; y0++) {
        for (int x0 = x - 1; x0 < x + 2; x0++) {
            int pos = 1;
            if (x0 >= 0 && x0 < w && y0 >= 0 && y0 < h)
                pos = (arr[x0][y0] > 0);
            m |= pos << i;
            i--;
        }
    }

    return off;
}

Vector3 tileset::defaultmap(int* arr, int x, int y, int w, int h) {
    short int m = 0;
    Vector3 off;
    int i = 11;
    for (int y0 = y - 1; y0 < y + 3; y0++) {
        for (int x0 = x - 1; x0 < x + 2; x0++) {
            int pos = 1;
            if (x0 >= 0 && x0 < w && y0 >= 0 && y0 < h)
                pos = arr[y0 * w + x0] > 0;
            m |= pos << i;
            i--;
        }
    }

    /*  
        1 1 1   1 1 1
        1 x 1   1 1 1
        1 1 1   0 0 0
        1 1 1   0 0 0

        how this works: 
            if (what must be wall && !(what must be floor))
    */
    if (m & 0b111111111111) // pure ceiling
        off = {6 * 16, 3 * 16, 1};
    if (!(m & 0b010111101000)) // pure floor
        off = {2 * 16, 3 * 16, 1};
    if (m & 0b010111111000 && !(m & 0b000000000111)) // center-bottom ceiling
        off = {2 * 16, 0 * 16, 1};
    if (m & 0b010111000000 && !(m & 0b000000111000)) // center wall
        off = {2 * 16, 1 * 16, 1};
    if (m & 0b010000000000 && !(m & 0b000111010000)) // top floor
        off = {2 * 16, 2 * 16, 1};
    if (m & 0b000000010000 && !(m & 0b010101000000)) // bottom floor
        off = {2 * 16, 4 * 16, 1};
    if (m & 0b000111111010 && !(m & 0b010000000000)) // center-bottom ceiling
        off = {2 * 16, 5 * 16, 1};
    if (m & 0b000010110010 && !(m & 0b000000001000)) // center-left ceiling
        off = {3 * 16, 0 * 16, 1};
    if (m & 0b000100000000 && !(m & 0b010010010000)) // left floor
        off = {3 * 16, 1 * 16, 1};
    if (m & 0b000001000000 && !(m & 0b010010010000)) // right floor
        off = {3 * 16, 3 * 16, 1};
    //else if (m & 0b && !(m & 0b))
    //    off = {3 * 16, 4 * 16, 1};
    //else if (m & 0b && !(m & 0b))
    //    off = {0 * 16, 0 * 16, 1};
    return off;

}
