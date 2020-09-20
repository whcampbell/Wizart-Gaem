#include <SDL.h>
#include <stdio.h>

const int WIDTH = 1200;
const int HEIGHT = 675;

SDL_Window* window = NULL;
SDL_Surface surface = NULL;
SDL_Renderer renderer = NULL;

bool initWindow() {
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL failed to initialize. Error: \n" << SDL_GetError();
        return false;
    }
    else {
        window = SDL_CreateWindow("Wizart Gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "Window creation failed. Error: \n" << SDL_GetError());
        } else {
            surface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateRenderer(window, -1, 0);
        }

    }
    return true;
}