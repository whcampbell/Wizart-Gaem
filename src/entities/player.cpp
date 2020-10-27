#include "entities/player.h"
#include "entitymanager.h"
#include "input.h"
#include "audio.h"
#include "camera.h"
#include "globals.h"
#include "entities/slash.h"
#include <iostream>
#include "fastmath.h"

    Player::Player() {
        idle = new Sprite("player1_idle");
        run = new Sprite("player1_run");
        *align->x_internal = 16;
        *align->y_internal = 16;
        activeSprite = idle;
        camera::bind(align);
        align->pos.x = 0;
        align->pos.y = 0;
    }

    void Player::update() {
        move_keyboard();
    }

    void Player::move_keyboard() {
        activeSprite = idle;

        if (key::down(SDL_SCANCODE_W) || key::down(SDL_SCANCODE_UP)) {
            align->pos.y -= speed;
            activeSprite = run;
        }
        if (key::down(SDL_SCANCODE_S) || key::down(SDL_SCANCODE_DOWN)) {
            align->pos.y += speed;
            activeSprite = run;
        }        
        if (key::down(SDL_SCANCODE_A) || key::down(SDL_SCANCODE_LEFT)) {
            align->flip = SDL_FLIP_HORIZONTAL;
            align->pos.x -= speed;
            activeSprite = run;
        }
        if (key::down(SDL_SCANCODE_D) || key::down(SDL_SCANCODE_RIGHT)) {
            align->flip = SDL_FLIP_NONE;
            align->pos.x += speed;
            activeSprite = run;
        }
        
        if (mouse::press(SDL_BUTTON_LEFT)){
            AttackSlash* attack = new AttackSlash();
            int dx = mouse::x() + camera::x_adj - align->pos.x;
            int dy = mouse::y() + camera::y_adj - align->pos.y;
            Alignment* align_attack = attack->pos();
            align_attack->pos.x = align->pos.x + 16 * cos(dx, dy);
            align_attack->pos.y = align->pos.y + 16 * sin(dx, dy);
            *align_attack->x_internal = 16;
            *align_attack->y_internal = 16;
            align_attack->theta = angle(dx, dy);
            entities::add(attack);
        }
            
    }
    
    void Player::move_controller() {

    }

    void Player::render() {
        activeSprite->render(align, camera::x, camera::y,  1);
    }

    Player::~Player() {

    }

