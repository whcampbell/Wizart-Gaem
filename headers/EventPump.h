#pragma once
#include <SDL.h>

namespace key {
    void update();
    
    void keydown(SDL_KeyboardEvent e);

    void keyup(SDL_KeyboardEvent e);
    
    void init();
}