#include "entities/spell_aoe.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include "components/physics.h"
#include "components/lifetime.h"
#include "utilities/combat.h"
#include <cmath>
#include "particle.h"
#include "sprite.h"

Spell_AOE::Spell_AOE() {
    Hitbox* box = registerHitbox("hitbox");
    box->align = align;
    // box->xoff = 16;
    // box->yoff = 16;
    box->w = 128;
    box->h = 128;

    activeSprite = NULL;
    // activeSprite = new Sprite("aoe");

    EntityList hit;
    *set<EntityList>() = hit;

    Lifetime life;
    life.ticks = 20;
    *set<Lifetime>() = life;
}

void Spell_AOE::update() {
    EntityList* hit = get<EntityList>();

    for (auto iterator : *entities::all()) {
       
        if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
            
            if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health = hp->health - 2;

                // damage number particle
                damagenumber(2, iterator->pos()->pos);

                // screen shake
                camera::screenshake(4, 9);

                // hitpause for target
                iterator->pause(6);

                // remove target if dead
                if (hp->health <= 0) 
                    entities::remove(iterator);
            }
        }
    }

    Lifetime* life = get<Lifetime>();
    life->ticks--;
    if (!life->ticks) 
        entities::remove(this);
}

void Spell_AOE::render() {
    // activeSprite->render(align, camera::x, camera::y, 2);
}

Spell_AOE::~Spell_AOE() {
    delete(activeSprite);
}