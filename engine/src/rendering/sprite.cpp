#include <SDL.h>
#include <SDL_image.h>
#include "internal/screen.h"
#include "internal/import.h"
#include "sprite.h"
#include <unordered_map>
#include "internal/resource.h"
#include "log.h"
#include <string>
#include "globals.h"
#include <vector>
#include "internal/renderrequest.h"
#include <algorithm>
#include <SDL_ttf.h>

static unsigned int RenderTime;
static std::vector<SDL_Texture*> toFree;

static std::unordered_map<std::string, Texture*>  spriteMap;
static std::vector<RenderRequest> requests;

Texture* getTexture(std::string name) {
	if (spriteMap.find(name) == spriteMap.end()) {
        log::out << log::err << name << " is not present in the sprite map" << log::endl;
        exit(1);
    }
	Texture* ptr = spriteMap[name];
	return ptr;
}

void imp::importSprite(std::string path) {
	
	imp::SpriteData data = imp::parseSprite(path);
	Texture* texture = new Texture(data.path);
	

	std::string name = data.name;

	SDL_Surface* surface = IMG_Load(data.path.c_str());
	if (surface == NULL) {
		log::out << log::err << "\tfailed to generate surface for image at " << data.path << "\n" << SDL_GetError() << log::endl;
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture->sheet == NULL) {
		log::out << log::err << "\tfailed to generate texture for image at " << data.path << "\n" << SDL_GetError() << log::endl;
		return;
	}
	SDL_FreeSurface(surface);

	texture->frames = data.frames;
	SDL_QueryTexture(texture->sheet, NULL, NULL, &(texture->w), &(texture->h));
	texture->w /= texture->frames;

	texture->clips = new SDL_Rect*[texture->frames];
	for (int i = 0; i < texture->frames; i++) {
		texture->clips[i] = new SDL_Rect{texture->w * i, 0, texture->w, texture->h};
	}

	SDL_DestroyTexture(texture->sheet);
	texture->sheet = nullptr;

	
	spriteMap[name] = texture;

	log::out << "\tmapping texture at " << name << log::endl;
	
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
	req.image.x0 = 0;
	req.image.y0 = 0;
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
	req.image.x0 = 0;
	req.image.y0 = 0;
	req.image.texture = texture;
	req.image.type = REQ_IMAGE;
	req.image.scale = GAME_SCALE;
	requests.push_back(req);
}

void Sprite::render(int x, int y, int x0, int y0, int w, int h, int z) {
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
	req.image.x0 = x0;
	req.image.y0 = y0;
	req.image.texture = texture;
	req.image.type = REQ_IMAGE;
	req.image.scale = GAME_SCALE;
	requests.push_back(req);
}


void spr::update() {
	RenderTime = SDL_GetTicks();
}

void spr::clean() {
	for (auto iterator = spriteMap.begin(); iterator != spriteMap.end(); iterator++) {
		iterator->second->update();
	}
}


void Texture::lazyload() {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		log::out << log::err << "error loading surface for sprite at " << path << log::endl;
		return;
	}

	sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (sheet == NULL) {
		log::out << log::err << "error generating texture for sprite at " << path << log::endl;
		return;
	}
	SDL_FreeSurface(surface);
	log::out << "lazyloaded sprite at " << path << log::endl;
}

void Texture::update() {
	if(loaded) {
		loaded--;
		if (!loaded)
			unload();
	}
}

void Texture::unload() {
	if (sheet != nullptr) {
		SDL_DestroyTexture(sheet);
		sheet = nullptr;
	}
	log::out << "unloaded sprite at " << path << log::endl;
}

void Texture::ping() {
	if (!loaded) {
		lazyload();
	}
	loaded = 30;
}

Text::Text(std::string text, int size, SDL_Color color) {
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

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = 0;
	req.text.type = REQ_TEXT;
	req.text.flip = SDL_FLIP_NONE;
	req.text.w = w;
	req.text.x = x;
	req.text.y = y;
	req.text.z = z;
	requests.push_back(req);
}
void Text::render(Alignment* align, int z){
	refresh();

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = align->theta;
	req.text.type = REQ_TEXT;
	req.text.flip = align->flip;
	req.text.w = w;
	req.text.x = align->pos.x - w/2;
	req.text.y = align->pos.y - h/2;
	req.text.z = z;
	requests.push_back(req);
}
void Text::render(Alignment* align, int xoff, int yoff, int z) {
	refresh();

	RenderRequest req;
	req.text.h = h;
	req.text.point = {w/2, h/2};
	req.text.scale = GAME_SCALE;
	req.text.texture = texture;
	req.text.theta = align->theta;
	req.text.type = REQ_TEXT;
	req.text.flip = align->flip;
	req.text.w = w;
	req.text.x = align->pos.x - w/2 - xoff;
	req.text.y = align->pos.y - h/2 - yoff;
	req.text.z = z;
	requests.push_back(req);
}

Text::~Text() {
	toFree.push_back(texture);
}

bool compareRequest(RenderRequest r1, RenderRequest r2) {
	return r1.z < r2.z || (r1.z == r2.z && r1.request.y < r2.request.y);
}

void spr::flush() {
	for (unsigned int i = 0; i < toFree.size(); i++) {
		SDL_DestroyTexture(toFree[i]);
		toFree.erase(toFree.begin() + i);
		i--;
	}
}

void spr::push() {
	std::sort(requests.begin(), requests.end(), compareRequest);
	for (unsigned int i = 0; i < requests.size(); i++)
		drawRequest(&requests[i]);
	requests.clear();
}

void spr::init() { 
	
}

Renderable::~Renderable() {

}

void render::drawRect(int x, int y, int w, int h, SDL_Color color, int z) {
	RenderRequest req;
	req.rect.h = h;
	req.rect.scale = GAME_SCALE;
	req.rect.type = REQ_RECT;
	req.rect.w = w;
	req.rect.x = x;
	req.rect.y = y;
	req.rect.z = z;
	req.rect.color1 = color;
	requests.push_back(req);
}

void render::fillRect(int x, int y, int w, int h, SDL_Color color, int z) {
	RenderRequest req;
	req.rect.h = h;
	req.rect.scale = GAME_SCALE;
	req.rect.type = REQ_FRECT;
	req.rect.w = w;
	req.rect.x = x;
	req.rect.y = y;
	req.rect.z = z;
	req.rect.color1 = color;
	req.rect.color2 = color;
	requests.push_back(req);
}

void render::outlineRect(int x, int y, int w, int h, SDL_Color color1, SDL_Color color2, int z) {
	RenderRequest req;
	req.rect.h = h;
	req.rect.scale = GAME_SCALE;
	req.rect.type = REQ_FRECT;
	req.rect.w = w;
	req.rect.x = x;
	req.rect.y = y;
	req.rect.z = z;
	req.rect.color1 = color1;
	req.rect.color2 = color2;
	requests.push_back(req);
}

void Sprite::setFrame(int f) {
	frame = f % texture->frames;
}