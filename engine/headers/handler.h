#pragma once
#include "scene.h"


/**
 * contains a number of functions related to running scenes in the game handler
 */ 
namespace hnd {
    
    /**
     * stops the currently running scene, and sets the input scene as the new scene
     * 
     * Scene* scene -   the new scene to set
     */ 
    void setScene(Scene* scene);
    
    /**
     * stops the currently running scene, and initalizes the input scene, then sets it as the new scene
     * 
     * Scene* scene -   the new scene to set
     */ 
    void initScene(Scene* scene);
}