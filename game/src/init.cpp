#include "engine.h"
#include "globals.h"
#include "handler.h"
#include "scenes/test.h"

void init() { 
    engine::setGameScale(3);
    scene::Test* scene = new scene::Test();
    hnd::initScene(scene);
}

int main(int argv, char** args) {
    ENGINE_DEV_MODE = true;
    engine::start(init);
    engine::stop();
    return 0;
}

