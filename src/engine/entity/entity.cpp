#include "entity.h"

Entity::Entity() {
    align = new Alignment();
}

void Entity::tick() {

}

Alignment* Entity::pos() {
    return align;
}

Entity::~Entity() {
    for (auto iterator = hitboxes.begin(); iterator != hitboxes.end(); iterator++)
        delete(iterator->second);
    delete(align);
}

Hitbox* Entity::hitbox(std::string name) {
    if (hitboxes.find(name) != hitboxes.end())
        return hitboxes[name];
    return nullptr;
}

Hitbox* Entity::registerHitbox(std::string name) {
    hitboxes[name] = new Hitbox();
    return hitboxes[name];
}

Hitbox* Entity::registerHitbox(std::string name, int w, int h, Alignment* alignment) {
    Hitbox* hitbox = new Hitbox();
    hitbox->w = w;
    hitbox->h = h;
    hitbox->align = alignment;
    hitboxes[name] = hitbox;
    return hitbox;
}
