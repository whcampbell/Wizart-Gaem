#include "sprite.h"
#include "vec.h"

class Tileset {
private:
    Sprite* sprite;
    int tilesize;
public:
    Tileset() {};
    Tileset(std::string name, int tilesize);
    void render(int x, int y, Vector3 map);
    ~Tileset();
};

namespace tileset {
    Vector3 defaultmap(int** arr, int x, int y, int w, int h);
    Vector3 defaultmap(int* arr, int x, int y, int w, int h);
};