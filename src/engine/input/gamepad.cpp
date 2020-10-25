#include "input.h"
#include "eventpump.h"
#include <SDL.h>
#include <vector>
#include <iostream>
#include <string.h>

struct Gamepad {
    SDL_GameController* controller = NULL;
    SDL_Haptic* haptics = NULL;
    bool key[SDL_CONTROLLER_BUTTON_MAX];
    bool key0[SDL_CONTROLLER_BUTTON_MAX];
    int id;
};

static std::vector<Gamepad*> controllers;

void gamepad::locateControllers() {
    controllers.clear();

    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        Gamepad* gamepad = new Gamepad();
        gamepad -> controller = SDL_GameControllerOpen(i);
        if (gamepad -> controller == NULL)
            std::cout << "Failed to initialize controller at index " << i << std::endl;
        gamepad ->haptics = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(gamepad->controller));
        if (gamepad ->haptics == NULL)
            std::cout << "No haptics found for controller at index " << i << std::endl;
        gamepad->id = i;
        controllers.push_back(gamepad);
    }
}

Gamepad* controller::getController(unsigned int index) {
    if (index < controllers.size())
        return controllers[index];
    return nullptr;
}

void gamepad::move(SDL_ControllerAxisEvent e) {

}

void gamepad::keyup(SDL_ControllerButtonEvent e) {
    for (unsigned int i = 0; i < controllers.size(); i++)
        if (controllers[i]->id == e.which)
            controllers[i]->key[e.button] = false;
}

void gamepad::keydown(SDL_ControllerButtonEvent e) {
    for (unsigned int i = 0; i < controllers.size(); i++)
        if (controllers[i]->id == e.which)
            controllers[i]->key[e.button] = true;
}

void gamepad::connect(SDL_ControllerDeviceEvent e) {

}

void gamepad::disconnect(SDL_ControllerDeviceEvent e) {

}

void gamepad::remap(SDL_ControllerDeviceEvent e) {

}

void gamepad::update() {
    for (unsigned int i = 0; i < controllers.size(); i++) {
        for(int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++)
            controllers[i]->key0[j] = controllers[i]->key[j];
    }
}

bool controller::down(Gamepad* gamepad, SDL_GameControllerButton button) {
    if (gamepad == nullptr)
        return false;
    return gamepad->key[button];
}

bool controller::press(Gamepad* gamepad, SDL_GameControllerButton button) {
    if (gamepad == nullptr)
        return false;
    return !gamepad->key0[button] && gamepad->key[button];
}

bool controller::release(Gamepad* gamepad, SDL_GameControllerButton button) {
    if (gamepad == nullptr)
        return false;
    return gamepad->key0[button] && !gamepad->key[button];
}

Vector controller::axis(Gamepad* gamepad, const char* name) {
    Vector pos = {0, 0};
    if (gamepad == nullptr)
        return pos;
    if (!strcmp(name, "left")) {
        pos.x = SDL_GameControllerGetAxis(gamepad->controller, SDL_CONTROLLER_AXIS_LEFTX);
        pos.y = SDL_GameControllerGetAxis(gamepad->controller, SDL_CONTROLLER_AXIS_LEFTY);
        return pos;
    }
    if (!strcmp(name, "right")) {
        pos.x = SDL_GameControllerGetAxis(gamepad->controller, SDL_CONTROLLER_AXIS_RIGHTX);
        pos.y = SDL_GameControllerGetAxis(gamepad->controller, SDL_CONTROLLER_AXIS_RIGHTY);
        return pos;
    }
    return pos;
}

