#pragma once
#include <SDL_mixer.h>
#include <string>

const int LOOP_INFINITELY = -1;

enum AudioContext {
    ADUIOCTX_scene, ADUIOCTX_engine
};

struct Mix {
private:
    int* loaded;
protected:
    std::string path;
    virtual void unload() {}
    virtual void lazyload() {}
public:
    Mix(std::string path) : path(path) {
        loaded = new int;
        *loaded = 0;
    }
    void update();
    void ping();
    virtual int play(int loops) {return -1;}
};

struct Mus : public Mix {
protected:
    void unload();
    void lazyload();
public:
    Mus(std::string path) : Mix(path) {}
    Mix_Music* data = nullptr;
    int play(int loops);
};

struct Sfx : public Mix{
protected:
    void unload();
    void lazyload();
public:
    Sfx(std::string path) : Mix(path) {}
    Mix_Chunk* data = nullptr;
    int play(int loops);
};

struct Sound {
private:
    Mix sound;
    int channel;
public:
    Sound(std::string name);

    int setVolume(int vol);

    void play(int loops);

    void stop();
};

class AudioSource {
public:
    int volume;

    Sound* play(std::string str);

    Sound* play(std::string str, AudioContext ctx);

    Sound* loop(std::string str, int loops);

    Sound* loop(std::string str, int loops, AudioContext ctx);

};

namespace hnd_sfx {
    void addSound(Sound* sound, AudioContext ctx);
}

namespace engine {
    AudioSource* getAudioSource(std::string name);
}