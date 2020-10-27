#include "entities/crate.h"
#include "camera.h"

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
    }

    void Crate::update() {}

    void Crate::render() {
        activeSprite->render(align, camera::x, camera::y, 1);
    }

    Crate::~Crate() {}

