#include <SDL_mixer.h>

const int LOOP_INFINITELY = -1;

enum AudioContext {
    Scene, Engine
};

struct Sound {
private:
    Mix_Chunk* sound;
    void lazyload();

    void update();

    void unload();
};

class AudioSource {

    Sound* play(const char* str);

    Sound* play(const char* str, AudioContext ctx);

    Sound* loop(const char* str, int loops);

    Sound* loop(const char* str, int loops, AudioContext ctx);

};