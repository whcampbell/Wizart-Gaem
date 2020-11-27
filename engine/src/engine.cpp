#include "internal/screen.h"
#include "log.h"
#include "engine.h"
#include <SDL_thread.h>
#include <SDL.h>
#include "internal/resource.h"
#include "internal/handler.h"
#include "internal/eventpump.h"

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
    hnd::update();
    spr::update();
}

bool flag_reswait = true;

int run(void* data) {
    while(flag_reswait);

    unsigned int lastu = SDL_GetTicks();
    unsigned int lastp = SDL_GetTicks();
    log::out << log::alert << "Starting game" << log::endl;

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
                sfx::clean();

                log::out << pdel << "ms since last update" << "\n\tFPS: " << (int)(fps * ((float)deltap / pdel))
                 << "\n\tUPS: " << (int)(ups * ((float)deltap / pdel)) << "\n\tAvg utime: " << (avgu / ups) << "ms" << log::endl;
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
		if (SDL_RenderClear(getRenderer())){
            log::out << log::err << "error clearing renderer: " << SDL_GetError() << log::endl;
        }

        hnd::render();
        spr::push();

		SDL_RenderPresent(getRenderer());

        spr::flush();
		fps++;
}

int runSDL(void* data) {
    unsigned int curr;
    unsigned int last = SDL_GetTicks();
    unsigned int delta = 1000;
	while (running) {
        curr = SDL_GetTicks();
        checkEvents();
        render();
        if (curr - last >= delta) {
            last = SDL_GetTicks();
            spr::clean();
        }
	}
    return 0;
}

void engine::start(void (*initfunc)()) {
    if (!initWindow()) {
        log::out << log::err << "Window initialization failed" << log::endl;
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
    log::out << log::alert << "Closing game" << log::endl;
    running = false;
    int threadReturn;
    SDL_WaitThread(eThread, &threadReturn);
    res::close();
    closeWindow();
}



