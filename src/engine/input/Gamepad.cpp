#include "Input.h"
#include <SDL.h>
#include <vector>
#include <iostream>

struct Gamepad {
    SDL_GameController* controller = NULL;
    SDL_Haptic* haptics = NULL;
};

std::vector<Gamepad*> controllers;

void locateControllers() {
    controllers.clear();

    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        Gamepad* gamepad = new Gamepad();
        gamepad -> controller = SDL_GameControllerOpen(i);
        if (gamepad -> controller == NULL)
            std::cout << "Failed to initialize controller at index " << i << std::endl;
        gamepad ->haptics = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(gamepad->controller));
        if (gamepad ->haptics == NULL)
            std::cout << "No haptics found for controller at index " << i << std::endl;
        controllers.push_back(gamepad);
    }
}

Gamepad* controller::getController(int index) {
    return controllers[index];
}