#include "entities/slash.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include <iostream>
#include "particle.h"


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

    static int lifetime() {
        return 60;
    }

    static void behavior(Vector2* vec, int t) {
        vec->y--;
    }

    void AttackSlash::update() {

        EntityList* hit = get<EntityList>();

        for (auto iterator : *entities::all()) {
            if (!(hit->contains(iterator)) && hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
                if (iterator->has<Hitpoints>()) {
                hit->list.push_back(iterator);
                Hitpoints* hp = iterator->get<Hitpoints>();
                hp->health--;

                // damage number particle
                Text* dmgnumber = new Text("1", 16, {255, 0, 0});
                ParticleSource* source = new ParticleSource(1, 10, dmgnumber, lifetime, behavior);
                source->bind(align->pos);
                source->start();
                // end damage number particle

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
        delete(activeSprite);
    }