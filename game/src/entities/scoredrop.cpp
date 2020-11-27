#include "entities/scoredrop.h"
#include "components/score.h"
#include "camera.h"

//ADD TO PLAYER WHEN YOU KNOW THIS WORKS
//Score sco;
//sco.scoreMax = 10000;
//sco.score = 0;
//sco.dropLvl = 1;
//*set<Score>() = sco;
//

ScoreDrop::ScoreDrop() {
    activeSprite = new Sprite("score_drop");
    *align->x_internal = 16;
    *align->y_internal = 16;
    Hitbox* hit = registerHitbox("hitbox");
    hit->align = align;
    hit->w = 16;
    hit->h = 16;
}

void ScoreDrop:: update() {
    for (auto iterator : *entities:: all()) {
        if (hitbox::collision(iterator->hitbox("pickupbox"), hitbox("hitbox"))) {
            if (iterator->has<Score>()) {

                Score* sco = iterator->get<Score>();
                sco->score += 2 * this->dropLvl;
                entities::remove(this);
                break;
            }
        }
    }
}

void ScoreDrop::render() {
    activeSprite->render(align, camera::x, camera::y, 2);
}

ScoreDrop::~ScoreDrop() {
    delete(activeSprite);
}