#include <SDL.h>
#include "EventPump.h"
#include "Input.h"
#include <string.h>

#define MOUSE_SCANCODES 384

bool keys[SDL_NUM_SCANCODES];
bool keys0[SDL_NUM_SCANCODES];
Uint16 map[SDL_NUM_SCANCODES];

Uint16 mouseCode(const char* name) {
    if (!strcmp(name, "MouseLeft"))
        return MOUSE_SCANCODES + SDL_BUTTON_LMASK;
    if (!strcmp(name, "MouseMiddle"))
        return MOUSE_SCANCODES + SDL_BUTTON_MIDDLE;
    if (!strcmp(name, "MouseRight"))
        return MOUSE_SCANCODES + SDL_BUTTON_RIGHT;
    if (!strcmp(name, "Mouse1"))
        return MOUSE_SCANCODES + SDL_BUTTON_X1;
    if (!strcmp(name, "Mouse2"))
        return MOUSE_SCANCODES + SDL_BUTTON_X2;
    return -1;
}

void key::update() {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
        keys0[i] = keys[i];
}

void key::init() {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) 
        map[i] = i;
}

void mouse::keyup(SDL_MouseButtonEvent e) {
    keys[map[MOUSE_SCANCODES + e.button]] = 0;
}

void mouse::keydown(SDL_MouseButtonEvent e) {
    keys[map[MOUSE_SCANCODES + e.button]] = 1;
}

bool mouse::down(const char* name) {
    return keys[mouseCode(name)];
}

bool mouse::press(const char* name) {
    return !keys0[mouseCode(name)] && keys[mouseCode(name)];
}

bool mouse::release(const char* name) {
    return keys0[mouseCode(name)] && !keys[mouseCode(name)];
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
    Uint16 code1 = 0;
    if ((code1 = mouseCode(phys)) == -1)
        code1 = SDL_GetScancodeFromKey(SDL_GetKeyFromName(phys));
    Uint16 code2;
    if ((code2 = mouseCode(vir)) == -1)
        code2 = SDL_GetScancodeFromKey(SDL_GetKeyFromName(vir));
    map[code1] = code2;
}