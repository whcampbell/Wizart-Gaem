#include "entity.h"
#include "sprite.h"

class HealthDrop : public Entity {
    private:
        Sprite* activeSprite;
    public:
        HealthDrop();
        void update();
        void render();
        ~HealthDrop();
};