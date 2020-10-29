#pragma once
#include "alignment.h"
#include "hitbox.h"
#include <unordered_map>
#include <string>
#include <bitset>
#include "component.h"
#include <iostream>

static int id_source;
static const int component_size = 128;

namespace component_i {
    using CID = std::size_t;

inline CID getCID() {
	static CID last = 0;
	return last++;
}

template <typename T> inline CID getCID() noexcept {
	static CID typeID = getCID();
	return typeID;
}
};

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
    int CID = component_i::getCID<T>();
	bitset[CID] = 1;
    
    if (component[CID] == nullptr) {
        component[CID] = new T;
    }  
	return (T*)(component[CID]);
}

template <typename T> bool has() {
	return bitset[component_i::getCID<T>()];
}

template <typename T> T* get() {
	return (T*)(component[component_i::getCID<T>()]);
}

template <typename T> void del() {
	bitset[component_i::getCID<T>()] = 0;
}
};


