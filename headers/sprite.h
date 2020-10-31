#pragma once
#include "alignment.h"
#include <string>
#include <memory>

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

struct Renderable {
public:
    virtual void render(int x, int y, int z) = 0;
    virtual void render(Alignment* align, int z) = 0;
    virtual void render(Alignment* align, int xoff, int yoff, int z) = 0;
};

struct Sprite : public Renderable {
private:
    Texture* texture;
	int frame;
    unsigned int anim_time;
public:
    unsigned int animDelta = 100;
    Sprite(std::string name);
    void render(int x, int y, int z);
    void render(Alignment* align, int z);
    void render(Alignment* align, int xoff, int yoff, int z);
    void render(int x, int y, int w, int h, int z);
};

struct Text : public Renderable {
private:
    int w, h;
    bool* valid;
    int* reading;
    std::string text;
    int size;
    SDL_Color color;
    bool u_flag = false;
    SDL_Texture* texture = nullptr;
    void refresh();
public:
    Text(std::string text, int size, SDL_Color color);
    ~Text();
    void update(std::string text);
    void update(int size);
    void update(SDL_Color color);
    void render(int x, int y, int z);
    void render(Alignment* align, int z);
    void render(Alignment* align, int xoff, int yoff, int z);
};