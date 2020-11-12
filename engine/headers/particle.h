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
    bool falign = false, offset = true;
    int size, loops, z;
    Particle* particles = nullptr;
    Renderable* sprite;
    void (*behavior)(Vector2*, int t);
    int (*lifetime)();
    void init();
public:
    ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t));
    ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t), int loops);
    void update();
    void render();
    void bind(Alignment* align);
    void bind(Vector2 vec);
    void toggleCameraOffset();
    void start();
    void stop();
    ~ParticleSource();
};

namespace particle {
    void flush();
}