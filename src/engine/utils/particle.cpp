#include "particle.h"

ParticleSource::ParticleSource(int size, Sprite* sprite, Vector (*pos)(), Vector (*behavior)(Alignment* align, int t), int (*lifetime)()) {

}

ParticleSource::ParticleSource(int size, Sprite* sprite, Vector (pos)(), Vector (*behavior)(Alignment* align, int t), int (*lifetime)(), int loops) {

}

void ParticleSource::update() {

}

void ParticleSource::render() {

}

ParticleSource::~ParticleSource() {

}