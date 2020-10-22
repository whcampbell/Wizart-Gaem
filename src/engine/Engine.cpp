#include "Screen.h"
#include <iostream>
#include "Engine.h"
#include <SDL_thread.h>
#include <SDL.h>
#include "ResourceManager.h"
#include "Handler.h"
#include "EventPump.h"

bool running = false;
static unsigned int fps, ups;
static unsigned int avgu;
SDL_Thread* rThread;

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

void run() {
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
            checkEvents();
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
}

void render() {
		SDL_RenderClear(getRenderer());

        hnd_i::render();

		SDL_RenderPresent(getRenderer());
		fps++;
}

int runSDL(void* data) {
	while (running) {
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
    res::init();
    running = true;
    rThread = SDL_CreateThread(runSDL, "renderThread", (void*)NULL);
    initfunc();
    run();
}

void engine::stop() {
    std::cout << "Closing game" << std::endl;
    running = false;
    int threadReturn;
    SDL_WaitThread(rThread, &threadReturn);
    res::close();
    closeWindow();
}



