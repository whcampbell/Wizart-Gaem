#include "entity.h"
#include "camera.h"

Entity::Entity() {
    align = new Alignment();
    for (int i = 0; i < component_size; i++)
        component[i] = nullptr;
}

void Entity::tick() {
    if (inactive)
        inactive--;
}

Alignment* Entity::pos() {
    return align;
}

Entity::~Entity() {
    for (auto iterator = hitboxes.begin(); iterator != hitboxes.end(); iterator++)
        delete(iterator->second);
    delete(align);
    for (int i = 0; i < component_size; i++)
        if (component[i] != nullptr)
            delete(component[i]);
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

void Entity::renderDevMode() {
    renderHitboxes(camera::x, camera::y);
}

void Entity::renderHitboxes(int xoff, int yoff) {
    for (auto iterator = hitboxes.begin(); iterator != hitboxes.end(); iterator++)
        hitbox::render(iterator->second, xoff, yoff);
}