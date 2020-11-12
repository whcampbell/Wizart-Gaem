#include "entities/projectile.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include <iostream>
#include <cmath>

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
                if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health--;
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
        
    }
