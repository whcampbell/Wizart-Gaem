#include "entity.h"
#include "sprite.h"

class XPDrop : public Entity {
private:
    Sprite* activeSprite;
public:
    XPDrop();
    void update();
    void render();
    ~XPDrop();
};