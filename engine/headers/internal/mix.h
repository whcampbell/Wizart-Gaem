#pragma once
#include <SDL_mixer.h>
#include <string>

/**
 * INTENRAL USE ONLY
 * generic audio data, virtual class
 */
struct Mix {
private:
    int* loaded;
protected:
    std::string path;
    virtual void unload() = 0;
    virtual void lazyload() = 0;
public:
    Mix(std::string path) : path(path) {
        loaded = new int;
        *loaded = 0;
    }
    
    /**
    * 
    */
    void update();

    /**
    * 
    */
    void ping();
    virtual int play(int loops) = 0;
};

/**
 * INTENRAL USE ONLY
 * Audio data representing music
 */
struct Mus : Mix {
protected:
    void unload();   
    void lazyload();
public:
    Mus(std::string path) : Mix(path) {}
    Mix_Music* data = nullptr;

    /**
    * 
    */
    int play(int loops);
};

/**
 * INTENRAL USE ONLY
 * Audio data representing a sound effect
 */
struct Sfx : Mix{
protected:
    void unload();
    void lazyload();
public:
    Sfx(std::string path) : Mix(path) {}
    Mix_Chunk* data = nullptr;

    /**
    * 
    */
    int play(int loops);
};