
#include "Import.h"
#include<unordered_map>
#include "Audio.h"
#include "ResourceManager.h"

std::unordered_map<const char*, Mix*> soundMap;

Mix getMix(const char* name) {
    Mix* ptr = soundMap[name];
    return *ptr;
}

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

int Mus::play(int loops) {
    Mix_PlayMusic(data, loops);
    return -2;
}

void Sfx::lazyload() {
    data = Mix_LoadWAV(path);
}

void Sfx::unload() {
    Mix_FreeChunk(data);
}

int Sfx::play(int loops) {
    return Mix_PlayChannel(-1, data, loops);
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
    Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    return sound;
}

Sound* AudioSource::play(const char* name, AudioContext ctx) {
        Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    return sound;
}

Sound* AudioSource::loop(const char* name, int loops) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    return sound;
}

Sound* AudioSource::loop(const char* name, int loops, AudioContext ctx) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    return sound;
}

void sfx_i::clean() {

}

Sound::Sound(const char* name) : sound(getMix(name)) {}

void Sound::play(int loops) {
    channel = sound.play(loops);
}

int Sound::setVolume(int vol) {
    if (channel == -2)
        return Mix_VolumeMusic(vol);
    else
        return Mix_Volume(channel, vol);
}

void Sound::stop() {
    if (channel == -2)
        Mix_HaltMusic();
    else
        Mix_HaltChannel(channel);
}
