#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "log.h"
#include "engine.h"

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 675;
float GAMESCALE_X = 1, GAMESCALE_Y = 1, TEXTSCALE_X = 1, TEXTSCALE_Y = 1;
int GAME_WIDTH = 1200 / GAMESCALE_X;
int GAME_HEIGHT = 675 / GAMESCALE_Y;
static float localGScale = 1, localTScale = 1;

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

bool initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        flog::out << flog::err << "SDL failed to initialize. Error: \n" << SDL_GetError() << flog::endl;
        return false;
    } else {
        if (TTF_Init() == -1) {
            flog::out << flog::err << "SDL_TTF failed to initialize. Error: \n" << SDL_GetError() << flog::endl;
            return false;
        }

        window = SDL_CreateWindow("Wizart Gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
        if (window == NULL) {
            flog::out << flog::err << "Window creation failed. Error: \n" << SDL_GetError() << flog::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer == NULL) {
                flog::out << flog::err << "Failed to create renderer" << SDL_GetError() << flog::endl;
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

static void updateScale() {
    GAMESCALE_X = localGScale * SCREEN_WIDTH / 1200.0;
    GAMESCALE_Y = localGScale * SCREEN_HEIGHT / 675.0;

    TEXTSCALE_X = localTScale * SCREEN_WIDTH / 1200.0;
    TEXTSCALE_Y = localTScale * SCREEN_HEIGHT / 675.0;

    GAME_WIDTH = SCREEN_WIDTH / GAMESCALE_X;
    GAME_HEIGHT = SCREEN_HEIGHT / GAMESCALE_Y;
}

void parseWindowEvent(SDL_WindowEvent e) {
    switch (e.event)
    {
        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
            updateScale();
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
            updateScale();
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
            updateScale();
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
            updateScale();
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
            updateScale();
            break;
    default:
        break;
    }
}

void engine::setGameScale(float gamescale) {
    localGScale = gamescale;
    updateScale();
}

void engine::setTextScale(float textscale) {
    localTScale = textscale;
    updateScale();
}

