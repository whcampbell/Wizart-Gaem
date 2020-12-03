#include "scenes/place_tiles.h"
#include "entities/player.h"
#include "entities/healthdrop.h"
#include "components/hitpoints.h"
#include "entities/speeddrop.h"
#include "entity.h"
#include "camera.h"
#include "globals.h"
#include "entities/crate.h"

Player* player;

Text* words;
int tile_size;
int room_size;
std::vector<Sprite*> room;
int map_size;
std::vector<std::vector<Sprite*>> map;

void initTiles() {
    room_size = 10;
    room.resize(map_size*map_size);
    tile_size = 16;
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
}


void scene::World::init() {
    initTiles();
    Player* player = new Player();
    entities::add(player);

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



    words = new Text("hello there", 28, {255, 255, 255});
}


void scene::World::update() {
    static int i = 0;

    if (!(i % 300)) {
        Crate* crate = new Crate();
        crate->pos()->pos.x = 64;
        crate->pos()->pos.y = 64;
        entities::add(crate);
    }

    i++;
}

void scene::World::render() {
    words->render(0, 0, 4);
    for (int y = 0; y < room_size; y++)
        for (int x = 0; x < room_size; x++)
            map[0][y*room_size + x]->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
}