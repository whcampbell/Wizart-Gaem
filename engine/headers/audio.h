#pragma once
#include <SDL_mixer.h>
#include <string>
#include <internal/mix.h>

const int LOOP_INFINITELY = -1;

/**
 * 
 */
enum AudioContext {
    ADUIOCTX_scene, ADUIOCTX_engine
};

/**
* 
*/
struct Sound {
private:
    Mix* sound;
    int channel;
public:
    Sound(std::string name);

    /**
    * 
    */
    int setVolume(int vol);

    /**
    * 
    */
    void play(int loops);

    /**
    * 
    */
    void stop();
};

/**
* 
*/
class AudioSource {
public:
    int volume = 64;

    /**
    * 
    */
    Sound* play(std::string str);

    /**
    * 
    */
    Sound* play(std::string str, AudioContext ctx);

    /**
    * 
    */
    Sound* loop(std::string str, int loops);

    /**
    * 
    */
    Sound* loop(std::string str, int loops, AudioContext ctx);

};

/**
* 
*/
namespace engine {

    /**
    * 
    */
    AudioSource* getAudioSource(std::string name);
}