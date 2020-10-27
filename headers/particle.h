#pragma once
#include "sprite.h"
#include "Alignment.h"

struct ParticleSource {
private:
    struct Particle {
        Alignment align;
        int lifetime;
    };
    Particle* particles;
    Sprite* sprite;
    int loops;
public:
    ParticleSource(int size, Sprite* sprite, Vector (*pos)(), Vector (*behavior)(Alignment* align, int t), int (*lifetime)());
    ParticleSource(int size, Sprite* sprite, Vector (pos)(), Vector (*behavior)(Alignment* align, int t), int (*lifetime)(), int loops);
    void update();
    void render();
    ~ParticleSource();
};