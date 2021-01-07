#pragma once
#include "vec.h"
#include <SDL.h>

/**
 * struct representing a single connected gamepad/controller
 */
struct Gamepad;

/**
 * contains functions for interfacing with mouse inputs
 */ 
namespace mouse {
    /**
     * gets the x position of the mouse relative to the screen (not the camera)
     * 
     * returns  -   the x position of the mouse
     */ 
    int x();

    /**
     * gets the y position of the mouse relative to the screen (not the camera)
     * 
     * returns  -   the y position of the mouse
     */ 
    int y();

    /**
     * gets the real x position of the mouse relative to the screen (not the camera)
     *
     * 
     * returns  -   the x position of the mouse
     */ 
    int x_adj();

    /**
     * gets the real y position of the mouse relative to the screen (not the camera)
     *
     * 
     * returns  -   the y position of the mouse
     */ 
    int y_adj();

    /**
     * checks whether the specified mouse button is currently down
     * 
     * Uint8 key    -   SDL_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button is down, false otherwise
     */ 
    bool down(Uint8 key);

    /**
     * checks whether the specified mouse button was pressed this frame (transitioned from up to down)
     * 
     * Uint8 key    -   SDL_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button was pressed this frame, false otherwise
     */ 
    bool press(Uint8 key);

    /**
     * checks whether the specified mouse button was released this frame (transitioned from down to up)
     *
     * Uint8 key    -   SDL_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button was released this frame, false otherwise
     */ 
    bool release(Uint8 key);
}

/**
 * contains functions for interfacing with keyboard inputs
 */ 
namespace key {
    
    /**
     * checks whether the specified key is currently down
     * 
     * Uint8 key    -   SDL_Scancode representing the key to check
     * returns      -   true if the key is down, false otherwise
     */ 
    bool down(SDL_Scancode name);

    /**
     * checks whether the specified key was pressed this frame (transitioned from up to down)
     * 
     * Uint8 key    -   SDL_Scancode representing the key to check
     * returns      -   true if the key was pressed this frame, false otherwise
     */ 
    bool press(SDL_Scancode name);

    
    /**
     * checks whether the specified key was released this frame (transitioned from down to up)
     *
     * Uint8 key    -   SDL_Scancode representing the key to check
     * returns      -   true if the key was released this frame, false otherwise
     */ 
    bool release(SDL_Scancode name);

    /**
     * remaps a key location, when the specified physical key is pressed, the game will treat
     * it as though the virtual key was pressed use an character to remap keyboard keys. for
     * remapping mouse buttons, use MouseLeft, MouseMiddle, MouseRight, Mouse1, and Mouse2
     * 
     * const char* phys -   text representation of the physical key that is pressed
     * const char* vir  -   text representation of the key that the engine should read as
     *                      pressed when the physical key is pressed
     */ 
    void remap(const char* phys, const char* vir);

}

/**
 * contains functions for interfacing with gamepad/controller inputs
 */ 
namespace controller {

    /**
     * tries to get a controller at the given index
     * 
     * unsigned int index   -   index to search for a controller at;
     * returns              -   a pointer to a Gamepad connected at the given
     *                          index, or null if no such gamepad exists
     */ 
    Gamepad* getController(unsigned int index);

    /**
     * checks if the given button is down on the given gamepad/controller
     * 
     * Gamepad* gamepad                 -   a pointer to the gamepad to check
     * SDL_GameControllerButton button  -   the code of the button to check
     * returns                          -   true if the button is down, false otherwise   
     */
    bool down(Gamepad* gamepad, SDL_GameControllerButton button);

    /**
     * checks if the given button was pressed on the given gamepad/controller
     * 
     * Gamepad* gamepad                 -   a pointer to the gamepad to check
     * SDL_GameControllerButton button  -   the code of the button to check
     * returns                          -   true if the button was pressed on this
     *                                      frame, false otherwise   
     */
    bool press(Gamepad* gamepad, SDL_GameControllerButton button);

    /**
     * checks if the given button was released on the given gamepad/controller
     * 
     * Gamepad* gamepad                 -   a pointer to the gamepad to check
     * SDL_GameControllerButton button  -   the code of the button to check
     * returns                          -   true if the button was released on this
     *                                      frame, false otherwise   
     */
    bool release(Gamepad* gamepad, SDL_GameControllerButton button);

    /**
     * gets a representation of the gamepad stick position
     * 
     * Gamepad* gamepad -   a pointer to the gamepad whos stick should be checked
     * const char* name -   name of the stick to check, left for the left stick,
     *                      and right for the right
     * returns          -   a vector2 representation of the given stick's position
     *                      relative to 0, 0
     */
    Vector2 axis(Gamepad* gamepad, const char* name);

}