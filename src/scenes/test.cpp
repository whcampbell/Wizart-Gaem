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

    Crate* crate1 = new Crate();
    crate1->pos()->pos.x = 0;
    crate1->pos()->pos.y = 0;
    entities::add(crate1);
    Crate* crate2 = new Crate();
    crate2->pos()->pos.x = 32;
    crate2->pos()->pos.y = 32;
    entities::add(crate2);
    Crate* crate3 = new Crate();
    crate3->pos()->pos.x = 64;
    crate3->pos()->pos.y = 64;
    entities::add(crate3);
}

void scene::Test::update() {

}

void scene::Test::render() {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            tile_test->render(x * tile_size - camera::x, y * tile_size - camera::y, 0);
}