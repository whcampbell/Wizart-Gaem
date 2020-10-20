#pragma once

struct Gamepad;

namespace mouse {
    int x();
    int y();
}

namespace key {
    bool down(const char* name);
    bool press(const char* name);
    bool release(const char* name);
    void remap(const char* phys, const char* vir);
}

namespace controller {
    Gamepad* getController(int index);
}