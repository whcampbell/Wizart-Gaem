#pragma once
#include "entity.h"
#include "sprite.h"
#include "statemachine.h"

class Spell_AOE : public Entity {
    private:
        Sprite* activeSprite;
    public:
        Spell_AOE();
        void update();
        void render();
        ~Spell_AOE();
};