#include "engine.h"
#include "handler.h"
#include "scenes/test.h"

void init() { 
    scene::Test* scene = new scene::Test();
    hnd::initScene(scene);
}

int main(int argv, char** args) {
    engine::start(init);
    engine::stop();
    return 0;
}

