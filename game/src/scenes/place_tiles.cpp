#include "scenes/place_tiles.h"
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

Player* player;

<<<<<<< HEAD:game/src/scenes/place_tiles.cpp
Text* words;
=======
Sprite* tile_test;
>>>>>>> master:game/src/scenes/test.cpp
int tile_size;
int room_size;
std::vector<Sprite*> room;
int map_size;
std::vector<std::vector<Sprite*>> map;

void initTiles() {
    room_size = 10;
    room.resize(map_size*map_size);
    tile_size = 16;
<<<<<<< HEAD:game/src/scenes/place_tiles.cpp
    // assume square map
    for (int i = 0; i < room_size*room_size; i++) {
        int row = (int)(i / room_size);
        int col = i % room_size;
        if (row == 0 || col == 0 || row == room_size-1 || col == room_size-1) {
            room[i] = new Sprite("tile_test");
        } else {
            room[i] = new Sprite("tile_test2");
        }
    }
    map.resize(1);
    map[0] = room;
=======
    tile_test = new Sprite("tileset_dungeon");
>>>>>>> master:game/src/scenes/test.cpp
}


void scene::World::init() {
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


void scene::World::update() {
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

<<<<<<< HEAD:game/src/scenes/place_tiles.cpp
void scene::World::render() {
    words->render(0, 0, 4);
    for (int y = 0; y < room_size; y++)
        for (int x = 0; x < room_size; x++)
            map[0][y*room_size + x]->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
=======
void scene::Test::render() {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            tile_test->render(x * tile_size - camera::x, y * tile_size - camera::y, 16, 0, 16, 16, 0);
>>>>>>> master:game/src/scenes/test.cpp
}