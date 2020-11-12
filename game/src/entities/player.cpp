#include "entities/player.h"
#include "entitymanager.h"
#include "input.h"
#include "audio.h"
#include "camera.h"
#include "globals.h"
#include "entities/slash.h"
#include "entities/projectile.h"
#include <iostream>
#include "fastmath.h"
#include "hitbox.h"

#include "components/hitpoints.h"
#include "components/mana.h"
#include "components/movespeed.h"


Player::Player() {
        idle = new Sprite("player1_idle");
        run = new Sprite("player1_run");
        hp_icon = new Sprite("health_icon");
        mp_icon = new Sprite("mana_icon");

        *align->x_internal = 16;
        *align->y_internal = 16;
        activeSprite = idle;
        camera::bind(align);
        align->pos.x = 0;
        align->pos.y = 0;

        Hitbox* pickup = registerHitbox("pickupbox");
        pickup->xoff = -8;
        pickup->yoff = -8;
        pickup->w = 32;
        pickup->h = 32;
        pickup->align = align;


        Hitpoints hp;
        hp.healthMax = 3;
        hp.health = hp.healthMax;
        *set<Hitpoints>() = hp;

        Mana mp;
        mp.manaMax = 3;
        mp.mana = mp.manaMax;
        *set<Mana>() = mp;

        Movespeed move;
        move.speed = 1;
        *set<Movespeed>() = move;
    }

    void Player::update() {
        move_keyboard();
    }

    void Player::move_keyboard() {
        activeSprite = idle;
        float speed = get<Movespeed>()->speed;
        
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

        if (mouse::press(SDL_BUTTON_RIGHT)){
            if (get<Mana>()->mana >= 1) {
                AttackProjectile* attack = new AttackProjectile();
                int dx = mouse::x() + camera::x_adj - align->pos.x;
                int dy = mouse::y() + camera::y_adj - align->pos.y;
                Alignment* align_attack = attack->pos();
                align_attack->pos.x = align->pos.x + 16 * cos(dx, dy);
                align_attack->pos.y = align->pos.y + 16 * sin(dx, dy);
                *align_attack->x_internal = 16;
                *align_attack->y_internal = 16;
                align_attack->theta = angle(dx, dy);
                entities::add(attack);
                get<Mana>()->mana--;
            }
        }
            
    }
    
    void Player::move_controller() {

    }

    void Player::render() {

        Hitpoints* health = get<Hitpoints>();
        Mana* mana = get<Mana>();
        for (int i = 0; i < health->healthMax; i++) {
            if (i < health->health)
                hp_icon->render(16 * i, 0, 5);
            else
                ;
            
        }
        for (int i = 0; i < mana->manaMax; i++) {
            if (i < mana->mana)
                mp_icon->render(16 * i, 16, 5);
            else
                ;
        }
        activeSprite->render(align, camera::x, camera::y,  4);
    }

    Player::~Player() {

    }

