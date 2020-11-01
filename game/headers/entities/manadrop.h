#include "entity.h"
#include "sprite.h"

class ManaDrop : public Entity {
private:
    Sprite* activeSprite;
public:
    ManaDrop();
    void update();
    void render();
    ~ManaDrop();
};

