#pragma once
#include <SDL_mixer.h>
#include <string>
#include <internal/mix.h>

const int LOOP_INFINITELY = -1;

/**
 * represents the context which audio should play relative to. Any sounds with scene context will
 * stop playing on scene switch. Any sound with engine context will always play until stopped
 * manually
 */
enum AudioContext {
    ADUIOCTX_scene, ADUIOCTX_engine
};

/**
* Structure representing a single playable sound or musical effect
*/
struct Sound {
private:
    Mix* sound;
    int channel;
public:
    Sound(std::string name);

    /**
    * Sets the volume that this sound will play at
    */
    int setVolume(int vol);

    /**
    * plays this sound, looping an additional number of times equal to the input value
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