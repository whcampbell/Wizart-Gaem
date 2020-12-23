#include "entities/spell_aoe.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include "components/physics.h"
#include "components/lifetime.h"
#include "utilities/combat.h"
#include "fastmath.h"
#include "particle.h"
#include "sprite.h"

Spell_AOE::Spell_AOE() {
    Hitbox* box = registerHitbox("hitbox");
    box->align = align;
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
    float centerx = align->pos.x;
    float centery = align->pos.y;
    EntityList* hit = get<EntityList>();

    for (auto iterator : *entities::all()) {
       
        if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
            
            if (iterator->has<Physics>()) {
                float dx = iterator->pos()->pos.x - centerx;
                float dy = iterator->pos()->pos.y - centery;

                float mag = dx * dx + dy * dy;
                int shove = 0;
                if (mag < 50) 
                    shove = 4;
                else if (mag < 100)
                    shove = 3;
                else
                    shove = 2;
                
                Physics* physics = iterator->get<Physics>();
                physics->physicsActive = true;
                physics->velocity.x = shove * cos(dx, dy);
                physics->velocity.y = shove * sin(dx, dy);
                physics->acceleration.x = -.08 * cos(dx, dy);
                physics->acceleration.y = -.08 * sin(dx, dy);
            }

            if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health = hp->health - 2;

                // damage number particle
                damagenumber(2, iterator->pos()->pos);

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
    if (life->ticks == 19) {
        camera::screenshake(4, 9);
    }
}

void Spell_AOE::render() {
    // activeSprite->render(align, camera::x, camera::y, 2);
}

Spell_AOE::~Spell_AOE() {
    delete(activeSprite);
}