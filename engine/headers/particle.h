#pragma once
#include "sprite.h"
#include "alignment.h"

/**
 * structure representing a collection of identical particles
 */ 
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
    /**
     * creates a particles source
     * 
     * int size                             -   the max number of particles this
     *                                          source can support
     * int z                                -   the z level to draw particles from
     *                                          this source at
     * Renderable* sprite                   -   The image to use for this source's
     *                                          particles
     * int(*)() lifetime                    -   an integer function modeling liftime
     *                                          for an individual particle in ticks
     * void(*)(Vector2*, int t) behavior    -   an function which modifies the input
     *                                          Vector2 which represents the particle's
     *                                          position
     */ 
    ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t));

    /**
     * creates a particles source which is looped a number of times. use
     * -1 to loop infinitely
     * 
     * int size                             -   the max number of particles this
     *                                          source can support
     * int z                                -   the z level to draw particles from
     *                                          this source at
     * Renderable* sprite                   -   The image to use for this source's
     *                                          particles
     * int(*)() lifetime                    -   an integer function modeling liftime
     *                                          for an individual particle in ticks
     * void(*)(Vector2*, int t) behavior    -   an function which modifies the input
     *                                          Vector2 which represents the particle's
     *                                          position
     * int loops                            -   the number of times to loop, -1 to loop
     *                                          infinitely
     */ 
    ParticleSource(int size, int z, Renderable* sprite, int (*lifetime)(), void (*behavior)(Vector2*, int t), int loops);

    /**
     * runs calculations for all particles associated with this Source.
     * Engine calls this method, do not call it again unless you know 
     * what you are doing
     */ 
    void update();
    
    /**
     * draws all particles associated with this Source.
     * Engine calls this method, do not call it again unless you know 
     * what you are doing
     */ 
    void render();

    /**
     * sets the source of particles relative to an existing alignment
     * 
     * Alignment* align -   the alignment that the source should be made
     *                      relative to
     */ 
    void bind(Alignment* align);

    /**
     * sets the source of particles relative to a static position represented
     * by a Vector2
     * 
     * Vector2 vec  -   the position that the source should be made relative to
     */ 
    void bind(Vector2 vec);
    
    /**
     * toggles if this source should be rendered relative to the screen or camera.
     * set to camera relative by default
     */ 
    void toggleCameraOffset();
    
    /**
     * begins actively rendering and updating this source
     */ 
    void start();

    /**
     * stops this source from being actively updated or rendered
     */ 
    void stop();

    ~ParticleSource();
};

/**
 * contains methods for interfacing with all particle sources
 */ 
namespace particle {
    /**
     * stops and destroys all active particles
     */ 
    void flush();
}