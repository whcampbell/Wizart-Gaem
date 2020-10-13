#include <SDL_mixer.h>

const int LOOP_INFINITELY = -1;

enum AudioContext {
    Scene, Engine
};

struct Mix {
    Mix_Chunk* data;
    const char* path;
    
    Mix(const char* path) : path(path) {}
    
    void lazyload();

    void update();

    void unload();
};

struct Sound {
private:
    Mix sound;
public:
    
};

class AudioSource {

    Sound* play(const char* str);

    Sound* play(const char* str, AudioContext ctx);

    Sound* loop(const char* str, int loops);

    Sound* loop(const char* str, int loops, AudioContext ctx);

};