#pragma once
#include "entity.h"
#include "sprite.h"

class Player : public  Entity {
private:
    Sprite* activeSprite;
public:
    Player();
    void update();
    void render();
    ~Player();
};