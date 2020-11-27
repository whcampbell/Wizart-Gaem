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
    * 
    *  int vol  -   the volume to play this sound at
    */
    int setVolume(int vol);

    /**
    * plays this sound, looping an additional number of times equal to the input value
    * 
    * int loops -   the number of times to loop this sound
    */
    void play(int loops);

    /**
    * Stops this sound from playing if it is currently playing
    */
    void stop();
};

/**
* Represents a single audio source which manages several channels with a set volume
*/
class AudioSource {
public:
    int volume = 64;

    /**
    * Fetches a sound by name and plays it at the engine context
    * 
    * string str    -   The name of the sound to be played
    * returns       -   A pointer to the sound that is being played
    */
    Sound* play(std::string str);

    /**
    * Fetches a sound by name and plays it
    * 
    * string str        -   The name of the sound to be played
    * AudioContex ctx   -   The context under which the sound should be played
    * returns           -   A pointer to the sound that is being played
    */
    Sound* play(std::string str, AudioContext ctx);

    /**
    * Fetches a sound by name and plays it at the engine context a 
    * specific number of times
    * 
    * string str    -   The name of the sound to be played
    * int loops     -   The number of times to repeat the sound
    * returns       -   A pointer to the sound that is being played
    */
    Sound* loop(std::string str, int loops);


    /**
    * Fetches a sound by name and plays it a 
    * specific number of times
    * 
    * string str        -   The name of the sound to be played
    * int loops         -   The number of times to repeat the sound
    * AudioContex ctx   -   The context under which the sound should be played
    * returns           -   A pointer to the sound that is being played
    */
    Sound* loop(std::string str, int loops, AudioContext ctx);

};

/**
* Contains engine-level methods for interfacing with sounds
*/
namespace engine {

    /**
    * Fetches a specific audio source by name, or creates a new audio source under that name
    * if none exists
    * 
    * string name   -   name of the audio source to find/create
    * returns       -   a pointer to the audio source
    */
    AudioSource* getAudioSource(std::string name);
}