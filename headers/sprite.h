#pragma once
#include "Alignment.h"
#include <string>

struct Texture {
private:
	std::string path;
    int* loaded;

    void lazyload();
    void unload();
    
public:
	int w, h, frames, delta;
	SDL_Texture* sheet;
	SDL_Rect** clips;

	Texture(std::string path) : path(path) {
        loaded = new int;
        *loaded = 0;
    }

    Texture() : path(NULL) {}

    void update();
    void ping();
};

struct Sprite {
private:
    Texture texture;
	int frame;
    unsigned int anim_time;
public:
    unsigned int animDelta = 100;
    Sprite(std::string name);
    void render(int x, int y, int z);
    void render(Alignment* align, int z);
};