#include "entities/player.h"
#include "input.h"
#include "audio.h"
#include "camera.h"
#include "globals.h"
#include "entities/slash.h"
#include "entities/projectile.h"
#include "entities/spell_aoe.h"
#include "fastmath.h"
#include "hitbox.h"

#include "utilities/combat.h"

#include "components/entitytracker.h"
#include "components/hitpoints.h"
#include "components/mana.h"
#include "components/movespeed.h"
#include "components/bufftimers.h"
#include "components/physics.h"
#include "components/xp.h"

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
        xp_icon = new Sprite("exp_icon");
        xp_back = new Sprite("exp_back");

        *align->x_internal = 16;
        *align->y_internal = 16;
        activeSprite = sprites[0];
        camera::bind(align);
        align->pos.x = 0;
        align->pos.y = 0;

        Hitbox* pickup = registerHitbox("pickupbox");
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
        buff.onFire = 0;
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
        

        // update buff timers
        // speedboost buff
        if (get<BuffTimers>()->speedBoost > 0) 
            get<BuffTimers>()->speedBoost--;

        // on fire buff
        if (get<BuffTimers>()->onFire > 0) {
            get<BuffTimers>()->onFire--;
            if (get<BuffTimers>()->onFire % 120 == 0) {
                Hitpoints* hp = get<Hitpoints>();
                hp->health--;
                damagenumber(1, align->pos);
                if (hp->health >= 0)
                    entities::remove(this);
            }
        }        

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
            int dx = mouse::x() + camera::x - align->pos.x;
            int dy = mouse::y() + camera::y - align->pos.y;
            Alignment* align_attack = attack->pos();
            align_attack->pos.x = align->pos.x + 16 * cos(dx, dy);
            align_attack->pos.y = align->pos.y + 16 * sin(dx, dy);
            *align_attack->x_internal = 16;
            *align_attack->y_internal = 16;
            align_attack->theta = angle(dx, dy);
            EntityTracker source;
            source.target = this;
            *(attack->set<EntityTracker>()) = source;
            entities::add(attack);
        }

        if (mouse::press(SDL_BUTTON_RIGHT)){
            if (get<Mana>()->mana >= 2) {
                Spell_AOE* spell = new Spell_AOE();
                Alignment* align_spell = spell->pos();
                align_spell->pos.x = camera::x + mouse::x();
                align_spell->pos.y = camera::y + mouse::y() - 32;
                *align_spell->x_internal = 64;
                *align_spell->y_internal = 64;
                entities::add(spell);
                get<Mana>()->mana = get<Mana>()->mana - 2;

                /*
                int dx = mouse::x() + camera::x - align->pos.x;
                int dy = mouse::y() + camera::y - align->pos.y;
                Alignment* align_attack = attack->pos();
                align_attack->pos.x = align->pos.x + 16 * cos(dx, dy);
                align_attack->pos.y = align->pos.y + 16 * sin(dx, dy);
                *align_attack->x_internal = 16;
                *align_attack->y_internal = 16;
                align_attack->theta = angle(dx, dy);
                entities::add(attack);
                get<Mana>()->mana--;
                */
            }
        }
            
    }
    
    void Player::move_controller() {

    }

    void Player::render() {

        Hitpoints* health = get<Hitpoints>();
        Mana* mana = get<Mana>();
        XP* xp = get<XP>();

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

        for (int i = 0; i < xp->neededXP; i++) {
            if (i < xp->currXP) 
                xp_icon->render(6 * i, 212, 6 + i);
            xp_back->render(6 * i, 212, 5);
        }
        activeSprite->render(align, camera::x, camera::y,  4);
    }

    Player::~Player() {
        for (int i = 0; i < ANIM_MAX; i++)
            delete(sprites[i]);
        delete [] sprites;
    }

