#pragma once

/**
 * class representing a single gamestate and all behavior associated
 * with it
 */ 
class Scene {
public:
    
    /**
     * method called when using hnd::initscene(). Should contain
     * first time initialization behavior
     */ 
    virtual void init() {}

    /**
     * method called every tick of game logic (~60x a sec). LLogic
     * behavior should be handled here, rendering should never be
     * done from this method.
     */ 
    virtual void update() {}

    /**
     * method called as fast as the renderer will allow. All rendering
     * should be handled either in this method, or via functions called
     * from this method. Logic in render methods should be kept to a
     * minimum
     */ 
    virtual void render() {}

};