#include "scenes/TestScene.h"
#include "Audio.h"
#include "Input.h"

bool flip = true;
Gamepad* gamepad1, *gamepad2;

void scene::Test::init() {
    sprite = new Sprite("load_splash");
    align.pos.x = 1;
    align.pos.y = 1;
    engine::getAudioSource("test")->play("test_mus_wav");
    gamepad1 = controller::getController(0);
    gamepad2 = controller::getController(1);
}

void scene::Test::update() {
    if (flip) {
        align.pos.x += 3;
        if (align.pos.x >= 565)
            flip = !flip;
    } else {
        align.pos.x -= 3;
        if (align.pos.x <= 0)
            flip = !flip;
    }
    if (key::press(SDL_SCANCODE_A))
        flip = !flip;

    if (mouse::press(SDL_BUTTON_LEFT))
        flip = !flip;

    if (controller::press(gamepad1, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
        flip = !flip;

    if (controller::press(gamepad2, SDL_CONTROLLER_BUTTON_DPAD_UP))
        flip = !flip;
}

void scene::Test::render() {
    sprite->render(&align);
}