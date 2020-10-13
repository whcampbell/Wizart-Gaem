
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


Sound* AudioSource::play(const char* str) {

}

Sound* AudioSource::play(const char* str, AudioContext ctx) {
        
}

Sound* AudioSource::loop(const char* str, int loops) {

}

Sound* AudioSource::loop(const char* str, int loops, AudioContext ctx) {
        
}
