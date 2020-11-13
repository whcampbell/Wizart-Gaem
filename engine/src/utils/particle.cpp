#include "particle.h"
#include <vector>
#include <algorithm>
#include "internal/particle.h"
#include "camera.h"

static std::vector<ParticleSource*> all_particle;
static std::vector<ParticleSource*> to_add;
static std::vector<ParticleSource*> to_remove;

void particle::update() {
    for (unsigned int i = 0; i < all_particle.size(); i++) 
        all_particle[i]->update();

    if (to_add.size()) {
        all_particle.insert(all_particle.end(), to_add.begin(), to_add.end());
        to_add.clear();
    }

    if (to_remove.size()) {
        for (unsigned int i = 0; i < to_remove.size(); i++) {
            all_particle.erase(std::remove(all_particle.begin(), all_particle.end(), to_remove[i]));
            delete(to_remove[i]);
        }
        to_remove.clear();
    }

}

void particle::render() {
    for (unsigned int i = 0; i < all_particle.size(); i++) 
        all_particle[i]->render();
}

void particle::add(ParticleSource* p) {
    to_add.push_back(p);
}

void particle::remove(ParticleSource* p) {
    if (std::find(to_remove.begin(), to_remove.end(), p) == to_remove.end())
        to_remove.push_back(p);
}

void particle::flush() {
    to_remove.insert(to_remove.end(), all_particle.begin(), all_particle.end());
}



ParticleSource::ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t)) {
    this->size = size;
    this->loops = 0;
    this->sprite = sprite;
    this->lifetime = lifetime;
    this->behavior = behavior;
    this->z = z;
}

ParticleSource::ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t), int loops) {
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
            particles[i].lifetime--;
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
    if (offset)
        for (int i = 0; i < size; i++) {
            if (particles[i].lifetime)
                sprite->render(&particles[i].align, camera::x, camera::y, z);
        }
    else
        for (int i = 0; i < size; i++) {
            if (particles[i].lifetime)
                sprite->render(&particles[i].align, z);
        }
}

void ParticleSource::bind(Alignment* align) {
    if (falign)
        delete(align);
    this->align = align;
    falign = false;
}

void ParticleSource::bind(Vector2 vec) {
    if (falign)
        delete(align); 
    align = new Alignment();
    align->pos = vec;
    falign = true;
}

void ParticleSource::start() {
    init();
    particle::add(this);
}

void ParticleSource::stop() {
    particle::remove(this);
}

void ParticleSource::init() {
    if (particles != nullptr)
        delete(particles);
    particles = new Particle[size];
    if (align == nullptr) {
        for (int i = 0; i < size; i++) {
            particles[i].align.pos.x = 0;
            particles[i].align.pos.y = 0;
            
            particles[i].align.theta = 0;
            *particles[i].align.x_internal = 0;
            *particles[i].align.y_internal = 0;
            particles[i].align.flip = SDL_FLIP_NONE;

            particles[i].lifetime = lifetime();
        }
    } else {
        for (int i = 0; i < size; i++) {
            particles[i].align.pos = align->pos;

            particles[i].align.theta = 0;
            *particles[i].align.x_internal = 0;
            *particles[i].align.y_internal = 0;
            particles[i].align.flip = SDL_FLIP_NONE;

            particles[i].lifetime = lifetime();
        }
    }
}

void ParticleSource::toggleCameraOffset() {
    offset = !offset;
}

ParticleSource::~ParticleSource() {
    if (particles != nullptr)
        delete(particles);
    if (falign)
        delete(align);
    delete(sprite);
}