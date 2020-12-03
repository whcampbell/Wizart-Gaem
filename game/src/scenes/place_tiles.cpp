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
#include "log.h"

Player* player;

Sprite* tile_test;
int tile_size;
int room_size;
std::vector<int> room;
int map_size;
std::vector<std::vector<int>> map;
std::vector<Sprite*> floor_tiles;
std::vector<Sprite*> wall_tiles;

void initTiles() {
    room_size = 10;
    map_size = 4;
    room.resize(room_size*room_size);
    tile_size = 16;
    floor_tiles.resize(1);
    wall_tiles.resize(1);
    floor_tiles[0] = new Sprite("tile_test2");
    wall_tiles[0] = new Sprite("tile_test");
    // assume square map and generate identical rooms
    for (int i = 0; i < room_size*room_size; i++) {
        int row = (int)(i / room_size);
        int col = i % room_size;
        if (row == 0 || col == 0 || row == room_size-1 || col == room_size-1) {
            room[i] = 1;
        } else {
            room[i] = 0;
        }
    }
    map.resize(map_size*map_size);
    for (int i = 0; i < map_size*map_size; i++) {
        map[i] = room;
    }
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

void scene::World::render() {
    Sprite* sprite;
    for (int i = 0; i < map_size*map_size; i++) {
        for (int y = 0; y < room_size; y++) {
            for (int x = 0; x < room_size; x++) {
                int row = (int)(i/map_size);
                int col = i % map_size;
                sprite = map[i][y*room_size + x] == 0 ? floor_tiles[0] : wall_tiles[0];
                sprite->render(x * tile_size - camera::x + tile_size*room_size*row, 
                    y * tile_size - camera::y + tile_size*room_size*col, 0);
            }
        }
    }
}