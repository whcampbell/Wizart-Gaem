#include "entities/slash.h"
#include "camera.h"
#include "entitymanager.h"

    AttackSlash::AttackSlash() {
        Hitbox* box = registerHitbox("hitbox");
        box->align = align;
        box->w = 16;
        box->h = 16;
        activeSprite = new Sprite("slash");
        ticks = 18;
    }

    void AttackSlash::update() {

        
        for (auto iterator : *entities::all()) {
            if (hitbox::collision(iterator->hitbox("hurtbox"), hitbox("hitbox"))) {
                entities::remove(iterator);
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