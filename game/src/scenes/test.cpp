#include "scenes/test.h"
#include "entities/player.h"
#include "entities/skeleton.h"
#include "entities/healthdrop.h"
#include "entities/scoredrop.h"
#include "components/hitpoints.h"
#include "entities/speeddrop.h"
#include "entity.h"
#include "camera.h"
#include "globals.h"
#include "entities/crate.h"
#include "entities/xpdrop.h"

Player* player;

Sprite* tile_test;
int tile_size;

void initTiles() {
    tile_size = 16;
    tile_test = new Sprite("tile_test");
}


void scene::Test::init() {
    initTiles();
    Player* player = new Player();
    entities::add(player);

    // Skeleton* skeleton = new Skeleton();
    // entities::add(skeleton);

    // lower player health and test health drop
    Hitpoints* hp = player->get<Hitpoints>();
    hp->health = 1;
    HealthDrop* hpDrop = new HealthDrop();
    hpDrop->pos()->pos.x = 100;
    hpDrop->pos()->pos.y = 64;
    entities::add(hpDrop);

    // Test speed drop
    SpeedDrop* spDrop = new SpeedDrop();
    spDrop->pos()->pos.x = 100;
    spDrop->pos()->pos.y = 100;
    entities::add(spDrop);

    ScoreDrop* scoDrop = new ScoreDrop();
    //scoDrop->dropAmount = 5;
    scoDrop->pos()->pos.x = 200;
    scoDrop->pos()->pos.y = 200;
    entities::add(scoDrop);

}


void scene::Test::update() {
    static int i = 0;

    if (!(i % 300)) {
    Crate* crate = new Crate();
    crate->pos()->pos.x = 64;
    crate->pos()->pos.y = 64;
    entities::add(crate);
    }

    if (!(i % 360)) {
    XPDrop* xpd = new XPDrop();
    xpd->pos()->pos.x = 96;
    xpd->pos()->pos.y = 96;
    entities::add(xpd);
    }

    i++;
}

void scene::Test::render() {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            tile_test->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
}