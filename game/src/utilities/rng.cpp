#include "utilities/rng.h"

void Noise::seed(int seed) {
    sd = seed;
}

void Noise::reseed(int seed) {
    sd = seed;
    sq = 0;
}

unsigned int Noise::rand() {


    constexpr unsigned int NOISE_1 = 0xAC66BDE1;
    constexpr unsigned int NOISE_2 = 0x386B1465;

    unsigned int v = sq;
    v *= NOISE_1;
    v ^= (v >> 8);
    v += sd;
    v ^= (v << 8);
    v *= NOISE_2;
    v ^= (v >> 8);
    sq++;
    return v;
}