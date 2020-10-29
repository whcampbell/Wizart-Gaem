#include "entities/slash.h"
#include "camera.h"
#include "entitymanager.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include <iostream>


    AttackSlash::AttackSlash() {
        Hitbox* box = registerHitbox("hitbox");
        box->align = align;
        box->w = 16;
        box->h = 16;
        activeSprite = new Sprite("slash");
        ticks = 18;
        EntityList hit;
        *set<EntityList>() = hit;
    }

    void AttackSlash::update() {

        EntityList* hit = get<EntityList>();

        for (auto iterator : *entities::all()) {
            if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
                if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health--;
                std::cout << hp->health << std::endl;
                if (hp->health <= 0)
                    entities::remove(iterator);
                }

            }
        }
        
        ticks--;
        if (!ticks)
            entities::remove(this);
    }

    void AttackSlash::render() {
        activeSprite->render(align, camera::x, camera::y, 2);
    }

    AttackSlash::~AttackSlash() {
        
    }