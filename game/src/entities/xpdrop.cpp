#include "entities/xpdrop.h"
#include "components/xp.h"
#include "camera.h"
#include "entitymanager.h"

XPDrop::XPDrop() {
    activeSprite = new Sprite("exp_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
}

void XPDrop::update() {
    for (auto iterator : *entities::all()) { // iterates through all entities
        if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) { // if the entity has collided with an XP pickup
            if (iterator->has<XP>()) { // if this is an entity that accepts XP
                XP* xpt = iterator->get<XP>(); // gets xp of entity that collided
                if (1 == xpt->toNextLev) { // are they ready to level up?
                    for (auto allPlay : *entities::all()) { // levels up all players
                        if (allPlay->has<XP>()) {
                            allPlay->level++; 
                            allPlay->toNextLev = 10;
                            allPlay->xp = 0;
                        }
                    }
                } else { // otherwise, gives player 10 xp on collision
                    for (auto allPlay : *entities::all()) { 
                        if (allPlay->has<XP>()) {
                            allPlay->toNextLev -= 1;
                            allPlay->xp += 1;
                        }
                    }
                }
            }
            entities::remove(this);
            break;
        }
    }
}

void ManaDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 2);
}
ManaDrop::~ManaDrop() {}