#pragma once
#include "entity.h"
#include <vector>


namespace entity_i {
    void update();
    void render();
};

namespace entities {
    std::vector<Entity*>* Entities();
    void add(Entity* e);
    void remove(Entity* e);
    void clear();
};