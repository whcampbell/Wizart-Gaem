#include <SDL_mixer.h>

const int LOOP_INFINITELY = -1;

enum AudioContext {
    Scene, Engine
};

struct Mix {
private:
    int* loaded;
protected:
    const char* path;
    virtual void unload() {}
    virtual void lazyload() {}
public:
    Mix(const char* path) : path(path) {
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
    Mus(const char* path) : Mix(path) {}
    Mix_Music* data = nullptr;
    int play(int loops);
};

struct Sfx : public Mix{
protected:
    void unload();
    void lazyload();
public:
    Sfx(const char* path) : Mix(path) {}
    Mix_Chunk* data = nullptr;
    int play(int loops);
};

struct Sound {
private:
    Mix sound;
    int channel;
public:
    Sound(const char* name);

    int setVolume(int vol);

    void play(int loops);

    void stop();
};

class AudioSource {

    int volume;

    Sound* play(const char* str);

    Sound* play(const char* str, AudioContext ctx);

    Sound* loop(const char* str, int loops);

    Sound* loop(const char* str, int loops, AudioContext ctx);

};