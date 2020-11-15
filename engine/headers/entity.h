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
protected:
    int id = ++id_source;
    Alignment* align;
public:
    Entity();
    virtual void update() = 0;
    void tick();
    virtual void render() = 0;
    //void renderDevMode();
    Alignment* pos();
    virtual ~Entity() = 0;
    Hitbox* hitbox(std::string name);
    Hitbox* registerHitbox(std::string name);
    Hitbox* registerHitbox(std::string name, int w, int h, Alignment* alignment);
    
template <typename T> T* set() {
    int CID = INTERNAL_ONLY_COMPONENT::getCID<T>();
	bitset[CID] = 1;
    
    if (component[CID] == nullptr) {
        component[CID] = new T;
    }  
	return (T*)(component[CID]);
}

template <typename T> bool has() {
	return bitset[INTERNAL_ONLY_COMPONENT::getCID<T>()];
}

template <typename T> T* get() {
	return (T*)(component[INTERNAL_ONLY_COMPONENT::getCID<T>()]);
}

template <typename T> void del() {
	bitset[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 0;
}
};

namespace entities {
    std::vector<Entity*>* all();
    void add(Entity* e);
    void remove(Entity* e);
    void clear();
};


