#pragma once
#include "alignment.h"
#include "hitbox.h"
#include <unordered_map>
#include <string>
#include <bitset>
#include "component.h"
#include <iostream>
#include <vector>
#include "internal/entity.h"

static int id_source;
static const int component_size = 128;

class Entity {
private:
    Component* component[component_size];
    std::bitset<component_size> bitset;
    std::unordered_map<std::string, Hitbox*> hitboxes;
    int inactive = 0;
protected:
    int id = ++id_source;
    Alignment* align;

    /**
     * draws this entity's hitboxes to screen at a given offset
     * 
     * int xoff -   the x offset to subtract from the hitbox position
     * int yoff -   the y offset to subtract from the hitbox position
     */ 
    void renderHitboxes(int xoff, int yoff);
public:
    Entity();

    /**
     * Virtual method, when extending entity all game logic should be handled in this method
     */ 
    virtual void update() {}
    
    /**
     * Internal method for all entities, handles engine-level logic for all entities. 
     * DO NOT OVERRIDE
     */ 
    void tick();

    /**
     * Virtual method, when extending entity, all render calls should be handled in this method
     */ 
    virtual void render() {}

    /**
     * Only draws while in dev mode. By default, calls renderHitboxes
     */ 
    void renderDevMode();

    /**
     * returns - a pointer to this entity's alignment
     */ 
    Alignment* pos();


    virtual ~Entity() = 0;

    /**
     * Gets a registerd hitbox from an entity
     * 
     * string name  -   The name of the hitbox to find
     * returns      -   A pointer to the hitbox or if no hitbox exists under that name, null
     */ 
    Hitbox* hitbox(std::string name);

    /**
     * Creates and registers a new hitbox under a given name
     * 
     * string name  -   The name of the new hitbox
     * returns      -   A pointer to the newly created hitbox
     */ 
    Hitbox* registerHitbox(std::string name);

    /**
     * Creates and registers a new hitbox under a given name
     * 
     * string name          -   The name of the new hitbox
     * int w                -   The width of the hitbox
     * int h                -   The height of the hitbox
     * Alignment* alignment -   A pointer to an alignment representing this hitbox's position
     * returns              -   A pointer to the newly created hitbox
     */ 
    Hitbox* registerHitbox(std::string name, int w, int h, Alignment* alignment);

    /**
     * returns true if this entity is being actively updated and false otherwise
     */ 
    bool isActive() {
        return !inactive;
    }

    /**
     * stops this entity from being updated for a given count
     * 
     * int ticks    -   the number of ticks to stop updating for
     */ 
    void pause(int ticks) {
        inactive = ticks;
    }
    
    /**
     * allocates memory for a new component on this entity and returns a pointer to that space,
     * or if the component already exists on this entity, returns a pointer to the space that
     * it exists in.
     * 
     * typename T    -   the type of the new component
     */ 
    template <typename T> T* set() {
        int CID = INTERNAL_ONLY_COMPONENT::getCID<T>();
	    bitset[CID] = 1;
        
        if (component[CID] == nullptr) {
            component[CID] = new T;
        }  
        return (T*)(component[CID]);
    }

    /**
     * checks if this entity has a given component
     * 
     * typename T   -   the type of the component to check for
     * returns      -   true if this entity has a given component, and false otherwise
     */ 
    template <typename T> bool has() {
        return bitset[INTERNAL_ONLY_COMPONENT::getCID<T>()];
    }

    /**
     * gets a pointer to acomponent on an entity
     * 
     * typename T   -   the type of the component to get
     * returns      -   a pointer to the component or null if the entity does not have the given component
     */ 
    template <typename T> T* get() {
        if (bitset[INTERNAL_ONLY_COMPONENT::getCID<T>()])
            return (T*)(component[INTERNAL_ONLY_COMPONENT::getCID<T>()]);
        return nullptr;
    }

    /**
     * removes a component from this entity
     * 
     * typenname T  -   the type of the component to remove
     */ 
    template <typename T> void del() {
        bitset[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 0;
    }
};

 /**
 * contains a number of functions related to operations on the list of all active entities
 */ 
namespace entities {
    /**
     * gets a list of all active entities
     * 
     * returns  -   a pointer to the vector containing all entities
     */ 
    std::vector<Entity*>* all();

    /**
     * adds a new entity to the list of active entities
     * 
     * Entity* e    -   a pointer to the new entity to add
     */ 
    void add(Entity* e);

    /**
     * removes an entity from the list of active entities
     * 
     * Entity* e    -   a pointer to the new entity to remove
     */ 
    void remove(Entity* e);

    /**
     * clears the list of active entities completely
     */ 
    void clear();
};


