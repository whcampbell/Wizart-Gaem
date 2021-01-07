#include "entities/slash.h"
#include "camera.h"
#include "components/hitpoints.h"
#include "components/entitylist.h"
#include "components/physics.h"
#include "components/entitytracker.h"
#include "particle.h"
#include "text.h"
#include <cmath>


    AttackSlash::AttackSlash() {
        Hitbox* box = registerHitbox("hitbox");
        box->align = align;
        box->w = 16;
        box->h = 16;
        box->xoff = 8;
        box->yoff = 8;
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
                Text* dmgnumber = new Text("1", 16, {255, 0, 0});
                ParticleSource* source = new ParticleSource(1, 10, dmgnumber, lifetime, behavior);
                source->bind(align->pos);
                source->start();
                // end damage number particle

                //do screenshake
                camera::screenshake(2, 9);
                //end screenshake

                //do hitpause (target and source)
                iterator->pause(4);
                if (has<EntityTracker>())
                    get<EntityTracker>()->target->pause(4);
                //end hitpause

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