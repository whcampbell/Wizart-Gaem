#include "engine.h"
#include "globals.h"
#include "handler.h"
#include "scenes/place_tiles.h"

void init() { 
    scene::World* scene = new scene::World();
    hnd::initScene(scene);
}

int main(int argv, char** args) {
    ENGINE_DEV_MODE = true;
    engine::start(init);
    engine::stop();
    return 0;
}

