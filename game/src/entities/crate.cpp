#include "entities/crate.h"
#include "entities/manadrop.h"

#include "fastmath.h"
#include "camera.h"

#include "components/physics.h"
#include "components/hitpoints.h"

    static int i = 0;

    Crate::Crate() {
        Hitbox* box = registerHitbox("hurtbox");
        box->align = align;
        box->w = 16;
        box->h = 16;
        *align->x_internal = 16;
        *align->y_internal = 16;
        if (i%2)
            activeSprite = new Sprite("crate");
        else
            activeSprite = new Sprite("barrel");
        i++;

        Hitpoints hitpoints;
        hitpoints.healthMax = 3;
        hitpoints.health = hitpoints.healthMax;
        *set<Hitpoints>() = hitpoints;

        Physics physics;
        physics.velocity = {0, 0};
        physics.acceleration = {0,0};
        physics.physicsActive = false;
        *set<Physics>() = physics;
    }

    void Crate::update() {
        Physics* physics = get<Physics>();
        if (physics->physicsActive) {
            align->pos.x += physics->velocity.x;
            align->pos.y += physics->velocity.y;
            physics->velocity.x += physics->acceleration.x;
            physics->velocity.y += physics->acceleration.y;
            if (abs(physics->velocity.x) - .1 <= 0 && abs(physics->velocity.y) - .1 <= 0) {
                physics->physicsActive = false;
                physics->acceleration.x = 0;
                physics->acceleration.y = 0;
            }
        }
    }

    void Crate::render() {
        activeSprite->render(align, camera::x, camera::y, 4);
    }

    Crate::~Crate() {
        ManaDrop* drop = new ManaDrop();
        drop->pos()->pos = align->pos;
        entities::add(drop);
        delete(activeSprite);
    }

