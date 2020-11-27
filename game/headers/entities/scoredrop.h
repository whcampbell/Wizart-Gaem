#include "entity.h"
#include "sprite.h"

class ScoreDrop : public Entity {
    private:
        Sprite* activeSprite;
    public:
        ScoreDrop();
        void update();
        void render();
        ~ScoreDrop();
};