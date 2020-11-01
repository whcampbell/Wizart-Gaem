#include "screen.h"
#include <iostream>
#include "engine.h"
#include <SDL_thread.h>
#include <SDL.h>
#include "resource.h"
#include "handler.h"
#include "eventpump.h"

float GAME_SCALE = 3;

static bool running = false;
static unsigned int fps, ups;
static unsigned int avgu;
static SDL_Thread* eThread;

static void checkEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e))
	    switch (e.type) {
	    case SDL_QUIT:
		    running = false;
		    break;
        case SDL_MOUSEWHEEL:
            break;
        case SDL_MOUSEBUTTONUP:
            mouse::keyup(e.button);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse::keydown(e.button);
            break;  
        case SDL_MOUSEMOTION:
            mouse::move(e.motion);
            break;
        case SDL_CONTROLLERDEVICEADDED:
            gamepad::connect(e.cdevice);
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            gamepad::disconnect(e.cdevice);
            break;
        case SDL_CONTROLLERDEVICEREMAPPED:
            gamepad::remap(e.cdevice);
            break;
        case SDL_CONTROLLERAXISMOTION:
            gamepad::move(e.caxis);
            break;
        case SDL_CONTROLLERBUTTONUP:
            gamepad::keyup(e.cbutton);
            break;  
        case SDL_CONTROLLERBUTTONDOWN:
            gamepad::keydown(e.cbutton);
            break;
        case SDL_KEYUP:
            key::keyup(e.key);
            break;
        case SDL_KEYDOWN:
            key::keydown(e.key);
            break;
	    default:
		    break;
	    }
}

void update() {
    hnd_i::update();
    spr_i::update();
}

void manageResources() {
    spr_i::clean();
    sfx_i::clean();
}

bool flag_reswait = true;

int run(void* data) {
    while(flag_reswait);

    unsigned int lastu = SDL_GetTicks();
    unsigned int lastp = SDL_GetTicks();
    std::cout << "Starting game" << std::endl;

    unsigned int startu = 0;
    unsigned int pdel = 0;

    unsigned int delta = 1000 / 60;
    unsigned int deltap = 1000;

    fps = 0;
    ups = 0;
    avgu = 0;

    while (running)
    {
        if ((SDL_GetTicks() - lastu) >= delta) {
            ups++;
            startu = SDL_GetTicks();
            update();
            avgu += SDL_GetTicks() - startu;

            if ((pdel = SDL_GetTicks() - lastp) >= deltap) {
                manageResources();

                std::cout << pdel << "ms since last update" << "\n\tFPS: " << (int)(fps * ((float)deltap / pdel))
                 << "\n\tUPS: " << (int)(ups * ((float)deltap / pdel)) << "\n\tAvg utime: " << (avgu / ups) << "ms" << std::endl;
                ups = 0;
                fps = 0;
                avgu = 0;
                lastp = SDL_GetTicks();
            }
            lastu = SDL_GetTicks();
        }
    }
    return 0;
}

void render() {
		SDL_RenderClear(getRenderer());

        hnd_i::render();
        spr_i::push();

		SDL_RenderPresent(getRenderer());
		fps++;
}

int runSDL(void* data) {
	while (running) {
        checkEvents();
        render();
	}
    return 0;
}

void engine::start(void (*initfunc)()) {
    if (!initWindow()) {
        std::cout << "Window initialization failed" << std::endl;
        return;
    }
    gamepad::locateControllers();
    key::init();
    running = true;
    eThread = SDL_CreateThread(run, "engineThread", (void*)NULL);
    res::init();
    initfunc();
    flag_reswait = false;
    runSDL((void*)NULL);
}

void engine::stop() {
    std::cout << "Closing game" << std::endl;
    running = false;
    int threadReturn;
    SDL_WaitThread(eThread, &threadReturn);
    res::close();
    closeWindow();
}



