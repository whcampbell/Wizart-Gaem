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
                if (xpt->currXP == (xpt->neededXP-1)) { // are they ready to level up?
                    for (auto allPlay : *entities::all()) { // levels up all players
                        XP* all = allPlay->get<XP>(); // gets xp of entity that collided
                        if (all->has<XP>()) {
                            all->level++; 
                            all->neededXP = all->level*10; 
                            all->currXP = 0;
                        }
                    }
                } else { // otherwise, gives player 10 xp on collision
                    for (auto allPlay : *entities::all()) { 
                        XP* all = allPlay->get<XP>(); // gets xp of entity that collided
                        if (all->has<XP>()) {
                            all->currXP += 1;
                        }
                    }
                }
            }
            entities::remove(this);
            break;
        }
    }
}

void XPDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 2);
}
XPDrop::~XPDrop() {}