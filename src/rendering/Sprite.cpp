#include <SDL.h>
#include <SDL_image.h>
#include "Screen.h"
#include "Import.h"
#include "Sprite.h"
#include<unordered_map>



unsigned int RenderTime;

std::unordered_map<const char*, Texture> spriteMap;

Texture getTexture(const char* name) {
	return spriteMap.at(name);
}

void imp::importSprite(const char* path) {
	
	imp_i::SpriteData data = imp_i::parseSprite(path);
	Texture* texture = new Texture(data.path);
	
	const char* name = data.name;

	SDL_Surface* surface = IMG_Load(data.path);
	if (surface == NULL) {
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture == NULL) {
		return;
	}
	texture->frames = data.frames;
	SDL_QueryTexture(texture->sheet, NULL, NULL, &(texture->w), &(texture->h));
	texture->w /= texture->frames;

	texture->clips = new SDL_Rect*[texture->frames];
	for (int i = 0; i < texture->frames; i++) {
		texture->clips[i] = new SDL_Rect{texture->w * i, 0, texture->w, texture->h};
	}

	spriteMap[name] = *texture;
}

Sprite::Sprite(const char* name) : texture(spriteMap[name]), frame{0}, anim_time{SDL_GetTicks()} {}

void Sprite::init() {

}

void Sprite::lazyload() {

}

void  Sprite::render(int x, int y) {
	SDL_Rect renderQuad = {x, y, texture.w, texture.h};
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture.frames;
		anim_time = RenderTime;
	}
		
	SDL_RenderCopy(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad);
}

void  Sprite::render(Alignment* align) {
	SDL_Rect renderQuad = { align->x, align->y, texture.w, texture.h };
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture.frames;
		anim_time = RenderTime;
	}
	SDL_RenderCopyEx(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad, align->theta, align->getPoint(), align->flip);
}


void spr_i::update() {
	RenderTime = SDL_GetTicks();
}