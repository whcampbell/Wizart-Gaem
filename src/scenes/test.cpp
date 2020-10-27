#include "scenes/test.h"
#include "entities/player.h"
#include "entitymanager.h"
#include "camera.h"
#include "globals.h"
#include "entities/crate.h"

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
}


void scene::Test::update() {
    static int i = 0;

    if (!(i % 300)) {
    Crate* crate = new Crate();
    crate->pos()->pos.x = 64;
    crate->pos()->pos.y = 64;
    entities::add(crate);
    }

    i++;
}

void scene::Test::render() {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            tile_test->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
}