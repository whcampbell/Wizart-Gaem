#pragma once
#include "alignment.h"
#include "hitbox.h"
#include <unordered_map>
#include <string>



class Entity {
protected:
    Alignment* align;
    std::unordered_map<std::string, Hitbox*> hitboxes;
public:
    Entity();
    virtual void update() = 0;
    void tick();
    virtual void render() = 0;
    Alignment* pos();
    virtual ~Entity() = 0;
    Hitbox* hitbox(std::string name);
    Hitbox* registerHitbox(std::string name);
    Hitbox* registerHitbox(std::string name, int w, int h, Alignment* alignment);
};