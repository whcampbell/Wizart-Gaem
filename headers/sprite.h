#pragma once
#include "Alignment.h"

struct Texture {
private:
	const char* path;
public:
	int w, h, frames, delta;
	SDL_Texture* sheet;
	SDL_Rect** clips;

	Texture(const char* path) : path(path) {}

    Texture() : path(NULL) {}
};

struct Sprite {
private:
    Texture texture;
	int frame, anim_time;
    void init();
    void lazyload();
public:
    int animDelta = 100;
    Sprite(const char* name);
    void render(float x, float y);
    void render(Alignment* align);
};

namespace spr_i {
    void update();
}