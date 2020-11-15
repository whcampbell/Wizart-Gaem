#pragma once

#include "entity.h"
#include "sprite.h"

class SpeedDrop : public Entity {
    private :
        Sprite* activeSprite;
    public :
        SpeedDrop();
        void update();
        void render();
        ~SpeedDrop();
};