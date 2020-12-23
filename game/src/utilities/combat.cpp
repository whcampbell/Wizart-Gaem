#include "particle.h"
#include "text.h"
#include "string"

static int lifetime() {
    return 60;
}

static void behavior(Vector2* vec, int t) {
    vec->y--;
}

void damagenumber(int amt, Vector2 align) {
    // damage number particle
    std::string stringAmt = std::to_string(amt);
    Text* dmgnumber = new Text(stringAmt, 16, {255, 0, 0});
    ParticleSource* source = new ParticleSource(1, 10, dmgnumber, lifetime, behavior);
    source->bind(align);
    source->start();
    // end damage number particle
}