#include "entity.h"
#include "sprite.h"
#include "vec.h"

class SpellDrop : public Entity {
    private:
        Sprite* activeSprite;
        Vector2 type;
    public:
        SpellDrop();
        void update();
        void render();
        ~SpellDrop();
};