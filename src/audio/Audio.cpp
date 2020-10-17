#include <iostream>
#include "Import.h"
#include<unordered_map>
#include "Audio.h"
#include "ResourceManager.h"
#include <string>
#include "Handler.h"

std::unordered_map<std::string, Mix*>* soundMap = new std::unordered_map<std::string, Mix*>();

Mix getMix(std::string name) {
    Mix* ptr = (*soundMap)[name];
    return *ptr;
}

void imp::importAudio(std::string path) {
    imp_i::SoundData data = imp_i::parseSound(path);

    std::cout << "\tcollecting data" << std::endl;
    
    std::string name = data.name;
    if (data.isMus) {
        Mus* sound = new Mus(data.path);
        (*soundMap)[name] = sound;
    } else {
        Sfx* sound = new Sfx(data.path);
        (*soundMap)[name] = sound;
    }

    std::cout << "\tmapping sound" << std::endl;
}

void Mus::lazyload() {
    data = Mix_LoadMUS(path.c_str());
}

void Mus::unload() {
    Mix_FreeMusic(data);
}

int Mus::play(int loops) {
    ping();
    Mix_PlayMusic(data, loops);
    return -2;
}

void Sfx::lazyload() {
    data = Mix_LoadWAV(path.c_str());
}

void Sfx::unload() {
    Mix_FreeChunk(data);
}

int Sfx::play(int loops) {
    ping();
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

Sound* AudioSource::play(std::string name) {
    Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ADUIOCTX_engine);
    return sound;
}

Sound* AudioSource::play(std::string name, AudioContext ctx) {
        Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ctx);
    return sound;
}

Sound* AudioSource::loop(std::string name, int loops) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ADUIOCTX_engine);
    return sound;
}

Sound* AudioSource::loop(std::string name, int loops, AudioContext ctx) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ctx);
    return sound;
}

void sfx_i::clean() {

}

Sound::Sound(std::string name) : sound(getMix(name)) {}

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
