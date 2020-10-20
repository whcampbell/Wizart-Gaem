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