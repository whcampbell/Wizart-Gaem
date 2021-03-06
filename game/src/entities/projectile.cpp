#include "entities/projectile.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include "components/physics.h"
#include "utilities/combat.h"
#include <cmath>
#include "particle.h"
#include "text.h"

    AttackProjectile::AttackProjectile() {
        Hitbox* box = registerHitbox("hitbox");
        box->align = align;
        box->w = 16;
        box->h = 16;
        activeSprite = new Sprite("projectile");
        ticks = 12;
        EntityList hit;
        *set<EntityList>() = hit;
    }

    void AttackProjectile::update() {

        align->pos.x += 5 * cos(align->theta * M_PI / 180);
        align->pos.y += 5 * sin(align->theta * M_PI / 180);
        EntityList* hit = get<EntityList>();

        for (auto iterator : *entities::all()) {
            if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {

                if (iterator->has<Physics>()) {
                    Physics* physics = iterator->get<Physics>();
                    physics->physicsActive = true;
                    physics->velocity.x = 2 * cos(align->theta * M_PI / 180);
                    physics->velocity.y = 2 * sin(align->theta * M_PI / 180);
                    physics->acceleration.x = -.08 * cos(align->theta * M_PI / 180);
                    physics->acceleration.y = -.08 * sin(align->theta * M_PI / 180);
                }

                if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health--;

                // damage number particle
                damagenumber(1, iterator->pos()->pos);
                // end damage number particle

                //do screenshake
                camera::screenshake(2, 9);
                //end screenshake

                //do hitpause (target only)
                iterator->pause(3);
                //end hitpause

                if (hp->health <= 0)
                    entities::remove(iterator);
                entities::remove(this);
                break;
                }
            }
        }
        
        ticks--;
        if (!ticks)
            entities::remove(this);
    }

    void AttackProjectile::render() {
        activeSprite->render(align, camera::x, camera::y, 2);
    }

    AttackProjectile::~AttackProjectile() {
        delete(activeSprite);
    }
