#include "Handler.h"
#include <vector>
#include "Audio.h"
#include <string>
#include <unordered_map>
#include <EventPump.h>

Scene* activeScene = nullptr;

std::vector<Sound*> engine_sounds;
std::vector<Sound*> scene_sounds;

std::unordered_map<std::string, AudioSource*>* audio_sources = new std::unordered_map<std::string, AudioSource*>();

void hnd_i::render() {
    if (activeScene != nullptr)
        activeScene->render();
}

void hnd_i::update() {
    if (activeScene != nullptr)
        activeScene->update();


    key::update();
}

void hnd::setScene(Scene* scene) {
    activeScene = scene;
}

void hnd::initScene(Scene* scene) {
    scene->init();
    activeScene = scene;
}

void hnd_sfx::addSound(Sound* sound, AudioContext ctx) {
    switch (ctx)
    {
    case ADUIOCTX_engine:
        engine_sounds.push_back(sound);
        break;
    case ADUIOCTX_scene:
        scene_sounds.push_back(sound);
        break;
    }
}

AudioSource* engine::getAudioSource(std::string name) {
    AudioSource* source;
    if (audio_sources->find(name) == audio_sources->end()) {
        source = new AudioSource();
        (*audio_sources)[name] = source;
    } else {
        source = (*audio_sources)[name];
    }
    return source;
}