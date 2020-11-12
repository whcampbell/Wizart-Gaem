#pragma once
#include "sprite.h"
#include "alignment.h"

struct ParticleSource {
private:
    struct Particle {
        Alignment align;
        int lifetime;
    };
    Alignment* align = nullptr;
    int size, loops, z;
    Particle* particles = nullptr;
    Sprite* sprite;
    void (*behavior)(Vector2*, int t);
    int (*lifetime)();
    void init();
public:
    ParticleSource(int size, int z, Sprite* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t));
    ParticleSource(int size, int z, Sprite* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t), int loops);
    void update();
    void render();
    void bind(Alignment* align);
    void start();
    void stop();
    ~ParticleSource();
};

namespace particle {
    void flush();
}