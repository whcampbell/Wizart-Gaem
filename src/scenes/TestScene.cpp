#include "scenes/TestScene.h"
#include "Audio.h"

bool flip = true;

void scene::Test::init() {
    sprite = new Sprite("load_splash");
    align.x = 1;
    align.y = 1;
    engine::getAudioSource("test")->play("test_mus");
}

void scene::Test::update() {
    if (flip) {
        align.x += 3;
        if (align.x >= 565)
            flip = !flip;
    } else {
        align.x -= 3;
        if (align.x <= 0)
            flip = !flip;
    }

}

void scene::Test::render() {
    sprite->render(&align);
}