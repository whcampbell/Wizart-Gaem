#include "component.h"
#include "entity.h"

struct EntityTracker : public Component {
    Entity* target;
};