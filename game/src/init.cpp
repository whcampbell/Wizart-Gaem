#include "engine.h"
#include "handler.h"
#include "scenes/place_tiles.h"

void init() { 
    scene::World* scene = new scene::World();
    hnd::initScene(scene);
}

int main(int argv, char** args) {
    engine::start(init);
    engine::stop();
    return 0;
}

