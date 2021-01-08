#include "entities/spelldrop.h"
#include "components/slots.h"
#include "camera.h"
#include "vec.h"

SpellDrop::SpellDrop() {
    activeSprite = new Sprite("spell_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
    hit->xoff = 8;
    hit->yoff = 8;

    // What spell is this, and what element (x is spell)
    // Currently hard coded to (AOE, fire)
    // should be random-ish eventually
    type.x = 1;
    type.y = 1;
}

void SpellDrop::update() {
    for (auto iterator : *entities:: all()) {
        if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) {
            if (iterator->has<Slots>()) {

                // currently selected spell will be replaced
                Slots* slots = iterator->get<Slots>();
                switch (slots->curr) {
                    case 1 :
                        slots->first = type;
                        break;
                    case 2 :
                        slots->second = type;
                        break;
                    case 3 :
                        slots->third = type;
                        break;
                }
                    
                
                entities::remove(this);
                break;
            }
        }
    }
}

void SpellDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 4);
}

SpellDrop::~SpellDrop() {
    delete(activeSprite);
}