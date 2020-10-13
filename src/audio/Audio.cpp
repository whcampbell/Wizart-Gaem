
#include "Import.h"
#include<unordered_map>
#include "Audio.h"

std::unordered_map<const char*, Sound> soundMap;

void imp::importAudio(const char* path) {

}

void Sound::lazyload() {

}

void Sound::update() {

}

void Sound::unload() {
        
}


Sound* AudioSource::play(const char* name) {
    return &soundMap[name];
}

Sound* AudioSource::play(const char* name, AudioContext ctx) {
    return &soundMap[name];
}

Sound* AudioSource::loop(const char* name, int loops) {
    return &soundMap[name];
}

Sound* AudioSource::loop(const char* name, int loops, AudioContext ctx) {
    return &soundMap[name];
}
