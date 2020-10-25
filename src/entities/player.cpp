#include "entities/player.h"
#include "entitymanager.h"
#include "input.h"
#include "audio.h"
#include "camera.h"

    Player::Player() {
        activeSprite = new Sprite("player1_idle");
        camera::bind(&align);
        align.pos.x = 0;
        align.pos.y = 0;
    }

    void Player::update() {
        if (key::down(SDL_SCANCODE_W) || key::down(SDL_SCANCODE_UP))
            align.pos.y--;
        if (key::down(SDL_SCANCODE_S) || key::down(SDL_SCANCODE_DOWN))
            align.pos.y++;            
        if (key::down(SDL_SCANCODE_A) || key::down(SDL_SCANCODE_LEFT))
            align.pos.x--;
        if (key::down(SDL_SCANCODE_D) || key::down(SDL_SCANCODE_RIGHT))
            align.pos.x++;

        if (key::press(SDL_SCANCODE_SPACE))
            engine::getAudioSource("SFX")->play("test_ogg");
    }

    void Player::render() {
        activeSprite->render(&align, camera::x, camera::y,  0);
    }

    Player::~Player() {

    }

