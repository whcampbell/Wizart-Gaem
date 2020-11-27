#pragma once

/**
 * functions for interacting with the core game engine
 */ 
namespace engine {
    
    /**
     * starts the game/game engine taking control away from the main thread,
     * then runs a target method once the engine has started
     * 
     * void (*initfunc)()   -   the function to run once the engine is started
     */ 
    void start(void (*initfunc)());

    /**
     * Stops the engine and cleans up all memory associated with the engine and renderer
     */ 
    void stop();
}
