#include "entities/speeddrop.h"
#include "components/movespeed.h"
#include "components/bufftimers.h"
#include "camera.h"

SpeedDrop:: SpeedDrop() {
    activeSprite = new Sprite("speed_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
}

void SpeedDrop:: update() {
    for (auto iterator : *entities:: all()) {
        if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) {
            if (iterator->has<Movespeed>() && iterator->has<BuffTimers>()) {

                // picking up a new speed drop will always refresh timer
                // to ten seconds (600 updates)
                Movespeed* sp = iterator->get<Movespeed>();
                BuffTimers* buff = iterator->get<BuffTimers>();
                buff->speedBoost = 600;
                entities::remove(this);
                break;
            }
        }
    }
}

void SpeedDrop:: render() {
    activeSprite->render(align, camera::x, camera::y, 2);
}

SpeedDrop:: ~SpeedDrop() {}