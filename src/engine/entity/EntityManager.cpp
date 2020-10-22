#include "EntityManager.h"
#include <vector>
#include <algorithm>

std::vector<Entity*> all_entity;
std::vector<Entity*> to_add;
std::vector<Entity*> to_remove;

void entity_i::update() {
    for (unsigned int i = 0; i < all_entity.size(); i++) {
        all_entity[i]->tick();
        all_entity[i]->update();
    }

    all_entity.insert(all_entity.end(), to_add.begin(), to_add.end());
    to_add.clear();
    for (unsigned int i = 0; i < to_remove.size(); i++) {
        all_entity.erase(std::remove(all_entity.begin(), all_entity.end(), to_remove[i]));
        delete(to_remove[i]);
    }
    to_remove.clear();
}

void entity_i::render() {
    for (unsigned int i = 0; i < all_entity.size(); i++) 
        all_entity[i]->render();
}

std::vector<Entity*>* entities::Entities() {
    return &all_entity;
}

void entities::add(Entity* e) {
    to_add.push_back(e);
}

void entities::remove(Entity* e) {
    to_remove.push_back(e);
}

void entities::clear() {
    to_remove.insert(to_remove.end(), all_entity.begin(), all_entity.end());
}