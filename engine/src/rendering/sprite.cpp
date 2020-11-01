#include <SDL.h>
#include <SDL_image.h>
#include "screen.h"
#include "import.h"
#include "sprite.h"
#include <unordered_map>
#include "resource.h"
#include <iostream>
#include <string>
#include "globals.h"
#include <vector>
#include "renderrequest.h"
#include <algorithm>
#include <SDL_ttf.h>

static unsigned int RenderTime;

static std::unordered_map<std::string, Texture*>*  spriteMap = new std::unordered_map<std::string, Texture*>();
static std::vector<RenderRequest> requests;

Texture* getTexture(std::string name) {
	if (spriteMap->find(name) == spriteMap->end()) {
        std::cout << name << " is not present in the sprite map" << std::endl;
        exit(1);
    }
	Texture* ptr = (*spriteMap)[name];
	return ptr;
}

void imp::importSprite(std::string path) {
	
	imp_i::SpriteData data = imp_i::parseSprite(path);
	Texture* texture = new Texture(data.path);
	
	std::cout << "\tcollecting data" << std::endl;

	std::string name = data.name;

	SDL_Surface* surface = IMG_Load(data.path.c_str());
	if (surface == NULL) {
		std::cout << "\tfailed to generate surface for image at " << data.path << "\n" << SDL_GetError() << std::endl;
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture->sheet == NULL) {
		std::cout << "\tfailed to generate texture for image at " << data.path << "\n" << SDL_GetError() << std::endl;
		return;
	}
	SDL_FreeSurface(surface);

	std::cout << "\tgenerating texture" << std::endl;

	texture->frames = data.frames;
	SDL_QueryTexture(texture->sheet, NULL, NULL, &(texture->w), &(texture->h));
	texture->w /= texture->frames;

	texture->clips = new SDL_Rect*[texture->frames];
	for (int i = 0; i < texture->frames; i++) {
		texture->clips[i] = new SDL_Rect{texture->w * i, 0, texture->w, texture->h};
	}

	std::cout << "\tcreating frame data" << std::endl;

	SDL_DestroyTexture(texture->sheet);


	
	(*spriteMap)[name] = texture;

	std::cout << "\tmapping texture at " << name << std::endl;
	
}

Sprite::Sprite(std::string name) : texture(getTexture(name)), frame{0}, anim_time{SDL_GetTicks()} {}

void  Sprite::render(int x, int y, int z) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}
	texture->ping();
	RenderRequest req;
	req.image.frame = frame;
	req.image.x = x;
	req.image.y = y;
	req.image.z = z;
	req.image.w = texture->w;
	req.image.h = texture->h;
	req.image.texture = texture;
	req.image.type = REQ_IMAGE;
	req.image.scale = GAME_SCALE;
	requests.push_back(req);
}

void  Sprite::render(Alignment* align, int z) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}
	texture->ping();
	RenderRequest req;
	req.sprite.frame = frame;
	req.sprite.x = align->pos.x - *align->x_internal;
	req.sprite.y = align->pos.y - *align->y_internal;
	req.sprite.z = z;
	req.sprite.w = texture->w;
	req.sprite.h = texture->h;
	req.sprite.texture = texture;
	req.sprite.type = REQ_SPRITE;
	req.sprite.scale = GAME_SCALE;
	req.sprite.theta = align->theta;
	req.sprite.point = *(align->getPoint());
	req.sprite.flip = align->flip;
	requests.push_back(req);
}

void  Sprite::render(Alignment* align, int xoff, int yoff, int z) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}
	texture->ping();
	RenderRequest req;
	req.sprite.frame = frame;
	req.sprite.x = align->pos.x - xoff - *align->x_internal;
	req.sprite.y = align->pos.y - yoff - *align->y_internal;
	req.sprite.z = z;
	req.sprite.w = texture->w;
	req.sprite.h = texture->h;
	req.sprite.texture = texture;
	req.sprite.type = REQ_SPRITE;
	req.sprite.scale = GAME_SCALE;
	req.sprite.theta = align->theta;
	req.sprite.point = *(align->getPoint());
	req.sprite.flip = align->flip;
	requests.push_back(req);
}

void Sprite::render(int x, int y, int w, int h, int z) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}
	texture->ping();
	RenderRequest req;
	req.image.frame = frame;
	req.image.x = x;
	req.image.y = y;
	req.image.z = z;
	req.image.w = w;
	req.image.h = h;
	req.image.texture = texture;
	req.image.type = REQ_IMAGE;
	req.image.scale = GAME_SCALE;
	requests.push_back(req);
}


void spr_i::update() {
	RenderTime = SDL_GetTicks();
}

void spr_i::clean() {
	for (auto iterator = spriteMap->begin(); iterator != spriteMap->end(); iterator++) {
		iterator->second->update();
	}
}


void Texture::lazyload() {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		return;
	}

	sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (sheet == NULL) {
		return;
	}
	SDL_FreeSurface(surface);
	std::cout << "lazyloaded sprite at " << path << std::endl;
}

void Texture::update() {
	if(loaded) {
		(loaded)--;
		if (!(loaded))
			unload();
	}
}

void Texture::unload() {
	SDL_DestroyTexture(sheet);
	std::cout << "unloaded sprite at " << path << std::endl;
}

void Texture::ping() {
	if (!(loaded)) {
		lazyload();
	}
	loaded = 30;
}

Text::Text(std::string text, int size, SDL_Color color) {
	valid = new bool;
	reading = new int;
	*reading = 0;
	*valid = true;

	update(text);
	update(size);
	update(color);
}

void Text::update(std::string text) {
	this->text = text;
	u_flag = true;
}

void Text::update(int size) {
	this->size = size;
	u_flag = true;
}

void Text::update(SDL_Color color) {
	this->color = color;
	u_flag = true;
}

void Text::refresh() {
	if (u_flag)  {

		if (texture != nullptr)
			SDL_DestroyTexture(texture);
		u_flag = false;
		TTF_Font* font = TTF_OpenFont("./res/IndieFantasy.ttf", size);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
	}
}

void Text::render(int x, int y, int z){
	refresh();
	(*reading)++;

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.reading = reading;
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = 0;
	req.text.type = REQ_TEXT;
	req.text.valid = valid;
	req.text.flip = SDL_FLIP_NONE;
	req.text.w = w;
	req.text.x = x;
	req.text.y = y;
	req.text.z = z;
	requests.push_back(req);
}
void Text::render(Alignment* align, int z){
	refresh();
	(*reading)++;

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.reading = reading;
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = align->theta;
	req.text.type = REQ_TEXT;
	req.text.valid = valid;
	req.text.flip = align->flip;
	req.text.w = w;
	req.text.x = align->pos.x - w/2;
	req.text.y = align->pos.y - h/2;
	req.text.z = z;
	requests.push_back(req);
}
void Text::render(Alignment* align, int xoff, int yoff, int z) {
	refresh();
	(*reading)++;

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.reading = reading;
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = align->theta;
	req.text.type = REQ_TEXT;
	req.text.valid = valid;
	req.text.flip = align->flip;
	req.text.w = w;
	req.text.x = align->pos.x - w/2 - xoff;
	req.text.y = align->pos.y - h/2 - yoff;
	req.text.z = z;
	requests.push_back(req);
}

Text::~Text() {
	SDL_SemWait(textsync);
	*valid = false;
	SDL_DestroyTexture(texture);
	SDL_SemPost(textsync);
}

bool compareRequest(RenderRequest r1, RenderRequest r2) {
	return r1.z < r2.z || (r1.z == r2.z && r1.request.y < r2.request.y);
}

void spr_i::push() {
	std::sort(requests.begin(), requests.end(), compareRequest);
	for (unsigned int i = 0; i < requests.size(); i++)
		drawRequest(&requests[i]);
	requests.clear();
}

void spr_i::init() {
	initRequestSystem();
}