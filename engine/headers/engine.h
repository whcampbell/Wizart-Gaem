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

    /**
     * Sets the gamescale and adjusts all nessecary screen variables. Note, the value stored
     * in the GAMESCALE_X/GAMESCALE_Y global may not match the value you set, as it is modified
     * to ensure that the game is rendered at a constant scale regardless of screen size
     */ 
    void setGameScale(float gamescale);

    /**
     * Sets the textscale and adjusts all nessecary screen variables. Note, the value stored
     * in the TEXTSCALE_X/TEXTSCALE_Y global may not match the value you set, as it is modified
     * to ensure that the game is rendered at a constant scale regardless of screen size
     */ 
    void setTextScale(float textscale);
}
