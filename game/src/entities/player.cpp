#include "entities/player.h"
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
#include "components/bufftimers.h"
#include "components/physics.h"
#include "components/xp.h"
#include <array>


static bool a_running;
static bool f_running() {return a_running;}
static bool f_idle() {return !a_running;}

Player::Player() {
        animator.init(sprites);
        animator.set(anim_idle);
        animator.link(anim_idle, anim_run, f_running);
        animator.link(anim_run, anim_idle, f_idle);

        hp_icon = new Sprite("health_icon");
        hp_back = new Sprite("health_back");
        mp_icon = new Sprite("mana_icon");
        mp_back = new Sprite("mana_back");

        *align->x_internal = 16;
        *align->y_internal = 16;
        activeSprite = sprites[0];
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

        XP xp;
        xp.neededXP = 5; // starts as 5 XP needed to advance to level 1
        xp.level = 0;
        xp.currXP = 0;
        *set<XP>() = xp;

        Mana mp;
        mp.manaMax = 3;
        mp.mana = mp.manaMax;
        *set<Mana>() = mp;

        Movespeed move;
        move.speed = 1;
        *set<Movespeed>() = move;

        BuffTimers buff;
        buff.speedBoost = 0;
        *set<BuffTimers>() = buff;

        Physics physics;
        physics.velocity = {0, 0};
        physics.acceleration = {0, 0};
        physics.physicsActive = false;
        *set<Physics>() = physics;
    }

    void Player::update() {
       
        if (!get<Physics>()->physicsActive) {
            move_keyboard();
        } else {
            Physics* physics = get<Physics>();
            align->pos.x += physics->velocity.x;
            align->pos.y += physics->velocity.y;
            physics->velocity.x += physics->acceleration.x;
            physics->velocity.y += physics->acceleration.y;
            if (abs(physics->velocity.x) - .1 <= 0 && abs(physics->velocity.y) - .1 <= 0) {
                physics->physicsActive = false;
                physics->acceleration.x = 0;
                physics->acceleration.y = 0;
            }
        }
        

        // update speed boost buff timer
        if (get<BuffTimers>()->speedBoost > 0) 
            get<BuffTimers>()->speedBoost--;

        animator.update();
        activeSprite = animator.read();
    }

    void Player::move_keyboard() {
        a_running = false;

        // if the speedboost timer is active, speed is set higher
        float speed = get<Movespeed>()->speed;
        if (get<BuffTimers>()->speedBoost > 0) {
            speed = 2;
        }
        
        
        if (key::down(SDL_SCANCODE_W) || key::down(SDL_SCANCODE_UP)) {
            align->pos.y -= speed;
            a_running = true;
        }
        if (key::down(SDL_SCANCODE_S) || key::down(SDL_SCANCODE_DOWN)) {
            align->pos.y += speed;
            a_running = true;
        }        
        if (key::down(SDL_SCANCODE_A) || key::down(SDL_SCANCODE_LEFT)) {
            align->flip = SDL_FLIP_HORIZONTAL;
            align->pos.x -= speed;
            a_running = true;
        }
        if (key::down(SDL_SCANCODE_D) || key::down(SDL_SCANCODE_RIGHT)) {
            align->flip = SDL_FLIP_NONE;
            align->pos.x += speed;
            a_running = true;
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
                hp_icon->render(7 * i, 0, 6 + i);
            hp_back->render(7 * i, 0, 5);
        }
        for (int i = 0; i < mana->manaMax; i++) {
            if (i < mana->mana)
                mp_icon->render(7 * i, 16, 6 + i);
            mp_back->render(7 * i, 16, 5);
        }
        activeSprite->render(align, camera::x, camera::y,  4);
    }

    Player::~Player() {
        for (int i = 0; i < ANIM_MAX; i++)
            delete(sprites[i]);
        delete [] sprites;
    }

