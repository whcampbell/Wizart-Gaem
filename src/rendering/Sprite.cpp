#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Screen.h"
#include "Alignment.h"

struct Texture {
public:
	int w, h, frames;
	SDL_Texture* sheet;
	SDL_Rect** clips;
};

#include<unordered_map>

std::unordered_map<const char*, Texture> spriteMap;

Texture getTexture(const char* name) {
	return spriteMap.at(name);
}

void LoadSprite(const char* path) {
	Texture* texture = new Texture();
	const char* name = nullptr; //TODO parse from metadata at path
	/* TODO build metafile parser
	texture->w = parse(path);
	texture->h = parse(path);
	texture->frames = (parsepath);
	texture->clips = new SDL_Rect*[texture->frames];
	for (int i = 0; i < frames; i++) {
		texture->clips[i] = &{texture->w * i, 0, texture->w, texture->h};
	}
	*/

	const char* imgPath = nullptr; //TODO parse from metadata at path
	SDL_Surface* surface = IMG_Load(imgPath);
	if (surface == NULL) {
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture == NULL) {
		return;
	}

	spriteMap[name] = *texture;
}




template <int frames> struct Sprite {
private:
	Texture texture;
	int frame;
public:

	Sprite(const char* name) {

	}

	void render(int x, int y) {
		SDL_Rect renderQuad = {x, y, texture.w, texture.h};
		/* TODO animation handling
		if (timedelta) 
		{
			frame++
			if (frame == texture.frames) 
				frame = 0;
		}
		 */
		SDL_RenderCopy(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad);
	}

	void render(Alignment* align) {
		SDL_Rect renderQuad = { align->x, align->y, texture.w, texture.h };
		/* TODO animation handling
		if (timedelta)
		{
			frame++
			if (frame == texture.frames)
				frame = 0;
		}
		*/
		SDL_RenderCopyEx(getRenderer(), texture.sheet, texture.clips[frame], &renderQuad, align->theta, align->getPoint(), align->flip);
	}

};