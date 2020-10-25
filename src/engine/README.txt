#include "Alignment.h"
    Includes the Alignment struct, which is used to represent the position and orientation of an object
    Alignment has these members:
        - pos: A vector representing the x, y position
        - x_internal: represents the center of the object, relative to the object's left side
        - y_internal: represents the center of the object, relative to the top of the object
        - theta: angle at which the object should be rotated
        - flip: sdl_flip value, determines if the object should be reversed either horizontally or vertically

#include "Audio.h"
    Includes the AudioContext enum with the values:
        - AUDIOCTX_scene
        - AUDIOCTX_engine
    Includes the Sound struct, which represents a currently playing sound
    Sound has these members
        - int setVolume(int vol): sets the volume of the sound, independent of the audio source
        - void play(int loops): plays the sound and loops it equal to the number of times
        - void stop(): stops the sound if it is currently playing
    Includes the AudioSource struct, which is used to represent a specific audio player, and holds values associated
    AudioSource has these members
        - volume: an integer ranging from 0 to 128, with a default of 64
        - Sound* play(std::string str): plays the sound mapped to the specifc string at the engine scale (you can see audio maps on startup, and in meta files)
        - Sound* play(std::string str, AudioContext ctx): plays the sound mapped to the specifc string at a scale corresponding to the ctx value
        - Sound* loop(std::string str, int loops): loops the sound mapped to the specific string at the engine scale the requested number of times. use LOOP_INFINITELY to loop until stopped
        - Sound* loop(std::string str, int loops, AudioContext ctx): loops the sound mapped to the specific string at the specified scale the requested number of times.
        The play and loop functions return a sound pointer for later management
    Includes the engine namespace, which holds functions of the engine related to Audio
    engine has  these  members:
        - AudioSource* getAudioSource(const char* name): returns the audiosource with the specific name, or creates it if it does not exist

#include "Camera.h"
    Includes the camera namespace which holds functions related to the camera
    
#include "Entity.h"
#include "EntityManager.h"
#include "Handler.h"
#include "Hitbox.h"
#include "Input.h"
#include "Scene.h"
#include "Sprite.h"
#include "StateMachine.h"
#include "Vector.h"
