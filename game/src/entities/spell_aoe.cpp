#include "entities/spell_aoe.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include "components/physics.h"
#include "components/lifetime.h"
#include "components/bufftimers.h"
#include "components/element.h"
#include "utilities/combat.h"
#include "fastmath.h"
#include "particle.h"
#include "sprite.h"

Spell_AOE::Spell_AOE() {
    Hitbox* box = registerHitbox("hitbox");
    box->align = align;
    box->w = 128;
    box->h = 128;
    box->yoff = 32;

    activeSprite = NULL;
    activeSprite = new Sprite("spell_explosion");

    EntityList hit;
    *set<EntityList>() = hit;

    Lifetime life;
    life.ticks = 72;
    *set<Lifetime>() = life;

    Element elm;
    elm.element = 0;
    *set<Element>() = elm;
}

void Spell_AOE::update() {

    EntityList* hit = get<EntityList>();
    Element* elm = get<Element>();
    int tag = elm->element;
    Lifetime* life = get<Lifetime>();
    if (life->ticks > 50)
    for (auto iterator : *entities::all()) {
       
        if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
            switch (tag) {
                case 1: // fire
                    cast(2, 3, 1, iterator);
                    break;
                case 2: // moist
                    cast(1, 4, 2, iterator);
                    break;
                case 3: // froze
                    cast(2, 0, 3, iterator);
                    break;
                case 4: 
                    // other elements should have different constants
                    break;
            }

        }
    }

    life->ticks--;
    if (!life->ticks) 
        entities::remove(this);
    if (life->ticks == 71) {
        camera::screenshake(5, 20);
    }
}

void Spell_AOE::cast(int damage, int knock, int dbuff, Entity* iterator) {
    EntityList* hit = get<EntityList>();
    float centerx = align->pos.x;
    float centery = align->pos.y + 32;
    if (iterator->has<Physics>() && knock > 0) {
        float dx = iterator->pos()->pos.x - centerx;
        float dy = iterator->pos()->pos.y - centery;

        float mag = dx * dx + dy * dy;
        int shove = 0;
        if (mag < 75) 
            shove = knock;
        else if (mag < 150)
            shove = knock - 1;
        else
            shove = knock - 2;
        
        Physics* physics = iterator->get<Physics>();
        physics->physicsActive = true;
        physics->velocity.x = shove * cos(dx, dy);
        physics->velocity.y = shove * sin(dx, dy);
        physics->acceleration.x = -.08 * cos(dx, dy);
        physics->acceleration.y = -.08 * sin(dx, dy);
    }

    if (iterator->has<BuffTimers>()) {
        BuffTimers* buff = iterator->get<BuffTimers>();
        if (dbuff == 1) 
            buff->onFire = 240;
        if (dbuff == 2) 
            buff->moist = 600;
        if (dbuff == 3)
            buff->frozen = 300;
    }

    if (iterator->has<Hitpoints>()) {
        hit->list.push_back(iterator);
        Hitpoints* hp = iterator->get<Hitpoints>();
        hp->health = hp->health - damage;

        // damage number particle
        damagenumber(damage, iterator->pos()->pos);

        // hitpause for target
        iterator->pause(6);

        // remove target if dead
        if (hp->health <= 0) 
            entities::remove(iterator);
    }
}

void Spell_AOE::render() {
    activeSprite->renderOnce(align, camera::x, camera::y, 4);
}

Spell_AOE::~Spell_AOE() {
    delete(activeSprite);
}