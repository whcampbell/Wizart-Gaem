#pragma once
#include "Alignment.h"

struct Texture {
private:
	const char* path;
    int* loaded;

    void lazyload();
    void unload();
    
public:
	int w, h, frames, delta;
	SDL_Texture* sheet;
	SDL_Rect** clips;

	Texture(const char* path) : path(path) {
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
    Sprite(const char* name);
    void render(int x, int y);
    void render(Alignment* align);
};