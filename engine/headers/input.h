#pragma once
#include "vec.h"
#include <SDL.h>

struct Gamepad;

namespace mouse {
    int x();
    int y();
    bool down(Uint8 key);
    bool press(Uint8 key);
    bool release(Uint8 key);
}

namespace key {
    bool down(SDL_Scancode name);
    bool press(SDL_Scancode name);
    bool release(SDL_Scancode name);
    void remap(const char* phys, const char* vir);
}

namespace controller {
    Gamepad* getController(unsigned int index);

    bool down(Gamepad* gamepad, SDL_GameControllerButton button);
    bool press(Gamepad* gamepad, SDL_GameControllerButton button);
    bool release(Gamepad* gamepad, SDL_GameControllerButton button);
    Vector axis(Gamepad* gamepad, const char* name);
}