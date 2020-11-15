#pragma once
#include <string>
#include <SDL.h>

struct Texture {
private:
	std::string path;
    int loaded;

    void lazyload();
    void unload();
    
public:
	int w, h, frames, delta;
	SDL_Texture* sheet;
	SDL_Rect** clips;

	Texture(std::string path) : path(path) {
        loaded = 0;
    }

    Texture() : path(NULL) {}

    void update();
    void ping();
};