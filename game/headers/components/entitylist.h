#pragma once
#include "component.h"
#include "entity.h"
#include <vector>
#include <algorithm>

struct EntityList : public Component {
    std::vector<Entity*> list;
    bool contains(Entity* entity) {
        return std::find(list.begin(), list.end(), entity) != list.end();
    }
};