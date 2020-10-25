#include "entity.h"

void Entity::tick() {

}

Alignment* Entity::pos() {
    return &align;
}

Entity::~Entity() {
    //why do you have to define a pure virtual deconstructor silly clown code
}