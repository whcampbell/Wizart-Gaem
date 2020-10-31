#include "entities/manadrop.h"
#include "components/mana.h"
#include "camera.h"
#include "entitymanager.h"

ManaDrop::ManaDrop() {
    activeSprite = new Sprite("mana_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
}

void ManaDrop::update() {
        for (auto iterator : *entities::all()) {
            if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) {
                if (iterator->has<Mana>()) {

                Mana* mp = iterator->get<Mana>();
                if (mp->mana == mp->manaMax)
                    continue;
                mp->mana += 2;
                std::cout << mp->mana << std::endl;
                if (mp->mana > mp->manaMax)
                    mp->mana = mp->manaMax;
                entities::remove(this);
                break;
            }
        }
    }
}

void ManaDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 2);
}
ManaDrop::~ManaDrop() {}

