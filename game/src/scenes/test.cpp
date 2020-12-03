#include "scenes/test.h"
#include "entities/player.h"
#include "entities/skeleton.h"
#include "entities/healthdrop.h"
#include "components/hitpoints.h"
#include "entities/speeddrop.h"
#include "entity.h"
#include "camera.h"
#include "globals.h"
#include "entities/crate.h"
#include "entities/xpdrop.h"
#include "tileset.h"

Player* player;

Tileset* tile_dungeon;
int map[100] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
                1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
                1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
                1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
                1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void initTiles() {
    tile_dungeon = new Tileset("tileset_dungeon", 16);
}


void scene::Test::init() {
    initTiles();
    Player* player = new Player();
    entities::add(player);

    Skeleton* skeleton = new Skeleton();
    entities::add(skeleton);

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
            tile_dungeon->render(x * 16 - camera::x, y * 16 - camera::y,
             tileset::defaultmap(map, x, y, 10, 10));
}