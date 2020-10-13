
#include "Import.h"
#include<unordered_map>
#include "Audio.h"

std::unordered_map<const char*, Mix*> soundMap;

void imp::importAudio(const char* path) {
    imp_i::SoundData data = imp_i::parseSound(path);
    const char* name = data.name;
    Mix* sound = new Mix(data.path);
    soundMap[name] = sound;
}

void Mix::lazyload() {

}

void Mix::update() {

}

void Mix::unload() {
        
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
