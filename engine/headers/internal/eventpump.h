#pragma once
#include <SDL.h>

namespace key {
    void update();
    
    void keydown(SDL_KeyboardEvent e);

    void keyup(SDL_KeyboardEvent e);
    
    void init();
}

namespace mouse {
    void move(SDL_MouseMotionEvent e); 

    void keyup(SDL_MouseButtonEvent e);

    void keydown(SDL_MouseButtonEvent e);
}

namespace gamepad {
    void update();

    void move(SDL_ControllerAxisEvent e);
    void keyup(SDL_ControllerButtonEvent e);
    void keydown(SDL_ControllerButtonEvent e);

    void connect(SDL_ControllerDeviceEvent e);
    void disconnect(SDL_ControllerDeviceEvent e);
    void remap(SDL_ControllerDeviceEvent e);

    void locateControllers();
}