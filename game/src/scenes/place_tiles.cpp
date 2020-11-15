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
int map_size;
std::vector<Sprite*> map;

void initTiles() {
    map_size = 10;
    map.resize(map_size*map_size);
    tile_size = 16;
    // assume square map
    for (int i = 0; i < map_size*map_size; i++) {
        map[i] = new Sprite("tile_test");
    }
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
    for (int y = 0; y < map_size; y++)
        for (int x = 0; x < map_size; x++)
            map[y*map_size + x]->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
}