#pragma once
#include "sprite.h"
#include "Alignment.h"

struct ParticleSource {
private:
    struct Particle {
        Alignment align;
        int lifetime;
    };
    int size;
    Particle* particles;
    Sprite* sprite;
    
public:
    ParticleSource(int size, Sprite* sprite, int (*lifetime)());
    ParticleSource(int size, Sprite* sprite, int (*lifetime)(), int loops);
    void update();
    void render();
    ~ParticleSource();
};