#include <SDL.h>
#include "EventPump.h"
#include "Input.h"

bool keys[SDL_NUM_SCANCODES];
bool keys0[SDL_NUM_SCANCODES];
Uint8 map[SDL_NUM_SCANCODES];

void key::update() {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
        keys0[i] = keys[i];
}

void key::init() {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) 
        map[i] = i;
}

void key::keydown(SDL_KeyboardEvent e) {
    keys[map[e.keysym.scancode]] = 1;
}

void key::keyup(SDL_KeyboardEvent e) {
    keys[map[e.keysym.scancode]] = 0;
}

bool key::down(const char* name) {
    return keys[SDL_GetScancodeFromKey(SDL_GetKeyFromName(name))];
}

bool key::press(const char* name) {
    SDL_Keycode code = SDL_GetKeyFromName(name);
    return !keys0[SDL_GetScancodeFromKey(code)] && keys[SDL_GetScancodeFromKey(code)];
}

bool key::release(const char* name) {
    SDL_Keycode code = SDL_GetKeyFromName(name);
    return keys0[SDL_GetScancodeFromKey(code)] && !keys[SDL_GetScancodeFromKey(code)];
}

void key::remap(const char* phys, const char* vir) {
    map[SDL_GetScancodeFromKey(SDL_GetKeyFromName(phys))] = SDL_GetScancodeFromKey(SDL_GetKeyFromName(vir));
}