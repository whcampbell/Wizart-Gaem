#include "entities/healthdrop.h"
#include "components/hitpoints.h"
#include "camera.h"

HealthDrop::HealthDrop() {
    activeSprite = new Sprite("life_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
}

void HealthDrop:: update() {
    for (auto iterator : *entities:: all()) {
        if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) {
            if (iterator->has<Hitpoints>()) {

                Hitpoints* hp = iterator->get<Hitpoints>();
                if (hp->health == hp->healthMax) 
                    continue;
                hp->health += 2;
                if (hp->health > hp->healthMax) 
                    hp->health = hp->healthMax;
                entities::remove(this);
                break;
            }
        }
    }
}

void HealthDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 4);
}

HealthDrop::~HealthDrop() {
    delete(activeSprite);
}