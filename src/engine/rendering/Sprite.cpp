#include <SDL.h>
#include <SDL_image.h>
#include "Screen.h"
#include "Import.h"
#include "Sprite.h"
#include <unordered_map>
#include "ResourceManager.h"
#include <iostream>
#include <string>


unsigned int RenderTime;

std::unordered_map<std::string, Texture*>*  spriteMap = new std::unordered_map<std::string, Texture*>();

Texture getTexture(std::string name) {
	if (spriteMap->find(name) == spriteMap->end()) {
        std::cout << name << " is not present in the sound map" << std::endl;
        exit(1);
    }
	Texture* ptr = (*spriteMap)[name];
	return *ptr;
}

void imp::importSprite(std::string path) {
	
	imp_i::SpriteData data = imp_i::parseSprite(path);
	Texture* texture = new Texture(data.path);
	
	std::cout << "\tcollecting data" << std::endl;

	std::string name = data.name;

	SDL_Surface* surface = IMG_Load(data.path.c_str());
	if (surface == NULL) {
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture->sheet == NULL) {
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

void  Sprite::render(int x, int y) {
	SDL_Rect renderQuad = {x, y, texture.w, texture.h};
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture.frames;
		anim_time = RenderTime;
	}
	texture.ping();
	SDL_RenderCopy(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad);
}

void  Sprite::render(Alignment* align) {
	SDL_Rect renderQuad = { align->pos.x, align->pos.y, texture.w, texture.h };
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture.frames;
		anim_time = RenderTime;
	}
	texture.ping();
	SDL_RenderCopyEx(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad, align->theta, align->getPoint(), align->flip);
}


void spr_i::update() {
	RenderTime = SDL_GetTicks();
}

void spr_i::clean() {
	
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
}

void Texture::update() {
	if(*loaded) {
		(*loaded)--;
		if (!(*loaded))
			unload();
	}
}

void Texture::unload() {
	SDL_DestroyTexture(sheet);
}

void Texture::ping() {
	if (!(*loaded)) {
		lazyload();
	}
	*loaded = 60;
}