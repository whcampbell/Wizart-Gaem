
#include "Import.h"
#include<unordered_map>
#include "Audio.h"
#include "ResourceManager.h"

std::unordered_map<const char*, Mix*> soundMap;

void imp::importAudio(const char* path) {
    imp_i::SoundData data = imp_i::parseSound(path);
    const char* name = data.name;
    if (data.isMus) {
        Mus* sound = new Mus(data.path);
        soundMap[name] = sound;
    } else {
        Sfx* sound = new Sfx(data.path);
        soundMap[name] = sound;
    }
}

void Mus::lazyload() {
    data = Mix_LoadMUS(path);
}

void Mus::unload() {
    Mix_FreeMusic(data);
}

void Sfx::lazyload() {
    data = Mix_LoadWAV(path);
}

void Sfx::unload() {
    Mix_FreeChunk(data);
}

void Mix::update() {
	if(*loaded) {
		(*loaded)--;
		if (!(*loaded))
			unload();
	}
}

void Mix::ping() {
    if (!(*loaded)) {
		lazyload();
	}
	*loaded = 60;
}

Sound* AudioSource::play(const char* name) {
    return nullptr;
}

Sound* AudioSource::play(const char* name, AudioContext ctx) {
    return nullptr;
}

Sound* AudioSource::loop(const char* name, int loops) {
    return nullptr;
}

Sound* AudioSource::loop(const char* name, int loops, AudioContext ctx) {
    return nullptr;
}

void sfx_i::clean() {

}
