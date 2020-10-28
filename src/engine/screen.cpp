#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>


static const int WIDTH = 1200;
static const int HEIGHT = 675;

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

bool initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL failed to initialize. Error: \n" << SDL_GetError() << std::endl;
        return false;
    } else {
        if (TTF_Init() == -1) {
            std::cout << "SDL_TTF failed to initialize. Error: \n" << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("Wizart Gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "Window creation failed. Error: \n" << SDL_GetError() << std::endl;
        } else {
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

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

SDL_Renderer* getRenderer() {
    return renderer;
}