#include <SDL.h>
#include <iostream>


static const int WIDTH = 1200;
static const int HEIGHT = 675;

static SDL_Window* window = NULL;
static SDL_Surface* surface = NULL;
static SDL_Renderer* renderer = NULL;

bool initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL failed to initialize. Error: \n" << SDL_GetError() << std::endl;
        return false;
    }
    else {
        window = SDL_CreateWindow("Wizart Gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "Window creation failed. Error: \n" << SDL_GetError() << std::endl;
        } else {
            surface = SDL_GetWindowSurface(window);
            if (surface == NULL) {
                std::cout << "Failed to create surface" << SDL_GetError() << std::endl;
                return false;
            }
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer == NULL) {
                std::cout << "Failed to create renderer" << SDL_GetError() << std::endl;
                return false;
            }
        }

    }
    return true;
}

void closeWindow() {
	SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    SDL_FreeSurface(surface);
	surface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

SDL_Renderer* getRenderer() {
    return renderer;
}