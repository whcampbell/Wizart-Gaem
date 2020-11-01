#include <iostream>
#include "import.h"
#include<unordered_map>
#include "audio.h"
#include "resource.h"
#include <string>
#include "handler.h"

static std::unordered_map<std::string, Mix*>* soundMap = new std::unordered_map<std::string, Mix*>();

Mix* getMix(std::string name) {
    if (soundMap->find(name) == soundMap->end()) {
        std::cout << name << " is not present in the sound map" << std::endl;
        exit(1);
    }
    Mix* ptr = (*soundMap)[name];
    return ptr;
}

void imp::importAudio(std::string path) {
    imp_i::SoundData data = imp_i::parseSound(path);

    std::cout << "\tcollecting data" << std::endl;
    
    std::string name = data.name;
    
    if (data.isMus) {
        Mus* sound = new Mus(data.path);
        (*soundMap)[name] = sound;
        std::cout << "\tmapping music at " << name << std::endl;
    } else {
        Sfx* sound = new Sfx(data.path);
        (*soundMap)[name] = sound;
        std::cout << "\tmapping sound at " << name << std::endl;
    }

    
}

void Mus::lazyload() {
    data = Mix_LoadMUS(path.c_str());
    std::cout << "lazyloaded music at " << path << std::endl;
}

void Mus::unload() {
    Mix_FreeMusic(data);
    std::cout << "unloaded music at " << path << std::endl;
}

int Mus::play(int loops) {
    ping();
    Mix_PlayMusic(data, loops);
    return -2;
}

void Sfx::lazyload() {
    data = Mix_LoadWAV(path.c_str());
    std::cout << "lazyloaded sound at " << path << std::endl;
}

void Sfx::unload() {
    Mix_FreeChunk(data);
    std::cout << "unloaded sound at " << path << std::endl;
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
	for (auto iterator = soundMap->begin(); iterator != soundMap->end(); iterator++) {
		iterator->second->update();
	}
}

Sound::Sound(std::string name) : sound(getMix(name)) {}

void Sound::play(int loops) {
    channel = sound->play(loops);
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

void sfx_i::init() {
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 8;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
        std::cout << "Unable to open audio!\n" << std::endl;
        exit(1);
    }

    if(Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD)
        std::cout << "error initializing sdl mixer" << std::endl;
}
