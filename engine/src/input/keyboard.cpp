#include <SDL.h>
#include "internal/eventpump.h"
#include "input.h"
#include <string.h>
#include <climits>

#define MOUSE_SCANCODES 384

static bool keys[SDL_NUM_SCANCODES];
static bool keys0[SDL_NUM_SCANCODES];
static Uint16 map[SDL_NUM_SCANCODES];

Uint16 mouseCode(const char* name) {
    if (!strcmp(name, "MouseLeft"))
        return MOUSE_SCANCODES + SDL_BUTTON_LEFT;
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

Uint16 mouseCode(Uint8 name) {
    if (name == SDL_BUTTON_LEFT)
        return MOUSE_SCANCODES + SDL_BUTTON_LEFT;
    if (name == SDL_BUTTON_MIDDLE)
        return MOUSE_SCANCODES + SDL_BUTTON_MIDDLE;
    if (name == SDL_BUTTON_RIGHT)
        return MOUSE_SCANCODES + SDL_BUTTON_RIGHT;
    if (name == SDL_BUTTON_X1)
        return MOUSE_SCANCODES + SDL_BUTTON_X1;
    if (name == SDL_BUTTON_X2)
        return MOUSE_SCANCODES + SDL_BUTTON_X2;
    return USHRT_MAX;
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

bool mouse::down(Uint8 key) {
    return keys[mouseCode(key)];
}

bool mouse::press(Uint8 key) {
    return !keys0[mouseCode(key)] && keys[mouseCode(key)];
}

bool mouse::release(Uint8 key) {
    return keys0[mouseCode(key)] && !keys[mouseCode(key)];
}

void key::keydown(SDL_KeyboardEvent e) {
    keys[map[e.keysym.scancode]] = 1;
}

void key::keyup(SDL_KeyboardEvent e) {
    keys[map[e.keysym.scancode]] = 0;
}

bool key::down(SDL_Scancode key) {
    return keys[key];
}

bool key::press(SDL_Scancode key) {
    return !keys0[key] && keys[key];
}

bool key::release(SDL_Scancode key) {
    return keys0[key] && !keys[key];
}

void key::remap(const char* phys, const char* vir) {
    Uint16 code1 = 0;
    if ((code1 = mouseCode(phys)) == USHRT_MAX)
        code1 = SDL_GetScancodeFromKey(SDL_GetKeyFromName(phys));
    Uint16 code2;
    if ((code2 = mouseCode(vir)) == USHRT_MAX)
        code2 = SDL_GetScancodeFromKey(SDL_GetKeyFromName(vir));
    map[code1] = code2;
}