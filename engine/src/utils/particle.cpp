#include "particle.h"

ParticleSource::ParticleSource(int size, int z, Sprite* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t)) {
    this->size = size;
    this->loops = 0;
    this->sprite = sprite;
    this->lifetime = lifetime;
    this->behavior = behavior;
    this->z = z;
}

ParticleSource::ParticleSource(int size, int z, Sprite* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t), int loops) {
    this->size = size;
    this->loops = loops;
    this->sprite = sprite;
    this->lifetime = lifetime;
    this->behavior = behavior;
    this->z = z;
}

void ParticleSource::update() {
    bool dead = true;
    for (int i = 0; i < size; i++) {
        if (particles[i].lifetime) {
            behavior(&particles[i].align.pos, particles[i].lifetime);
            dead = false;
        }
    }


    if (dead) {
        if (loops > 0) {
            init();
            loops--;
        } 
        else
            stop();
        
    }
}

void ParticleSource::render() {
    for (int i = 0; i < size; i++) {
        if (particles[i].lifetime)
            sprite->render(&particles[i].align, z);
    }
}

void ParticleSource::bind(Alignment* align) {
    this->align = align;
}

void ParticleSource::start() {
    init();
    //add to particle manager
}

void ParticleSource::stop() {
    //remove from particle manager and free
}

void ParticleSource::init() {
    if (particles != nullptr)
        delete(particles);
    particles = new Particle[size];
    if (align == nullptr) {
        for (int i = 0; i < size; i++) {
            particles[i].align.pos.x = 0;
            particles[i].align.pos.y = 0;
            particles[i].lifetime = lifetime();
        }
    } else {
        for (int i = 0; i < size; i++) {
            particles[i].align.pos = align->pos;
            particles[i].lifetime = lifetime();
        }
    }
}

ParticleSource::~ParticleSource() {
    if (particles != nullptr)
        delete(particles);
}