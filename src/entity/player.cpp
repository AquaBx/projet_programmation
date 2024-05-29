//
// Created by celia on 27/05/2024.
//
#include <algorithm>

#include "player.h"

#include "cluster.h"
#include "renderer.h"

#include "input.h"
#include "event.h"

#include "map/map.h"
#include "physics/physics.h"

player::player(vec2<float> pos, vec2<float> size, float max_health, float max_food, float max_copper) :
        entity(pos),
        animated_sprite(pos, size, {{48, 48}}, {{size.x / 2, size.y / 2}}, "../resources/player.png",
                        {4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},

                        0.1),
        collidable_entity(pos, aabb{24, 28, 32, 20}),
        max_health(max_health), current_health(max_health),
        max_food(max_food), current_food(0),
        max_copper(max_copper), current_copper(0),
        tick(0) {
}

void player::draw(const camera& cam) const {
    // collidable_entity::draw_collide_box(cam);
    sprite::draw(cam);
}

circle player::get_interact_zone() const {
    circle interact_zone{8, size / 2.0f};
    return interact_zone + get_position();
}

void player::update(float dt) {
    if(tick == map::map_tick) return;
    tick = map::map_tick;

    animated_sprite::update(dt);

    // perdre de la vie
    damage(dt);

    if(current_health <= 0.0f) {
        // notifier l'application que le joueur est mort
        event::manager::append(event::source::player);
    }

    // perdre de la nourriture
    //lose_food(dt);
    bool actioned = input::is_key_pressed(SDL_SCANCODE_E);

    vec2<float> dir{{0, 0}};

    const float speed = 50;
    if (sprite_offset.y < 4) {
        if (input::is_key_pressed(SDL_SCANCODE_A)) {
            dir.x -= 1;
            sprite_offset.y = 2;
        }
    
        if (input::is_key_pressed(SDL_SCANCODE_D)) {
            dir.x += 1;
            sprite_offset.y = 3;
        }
    
        if (input::is_key_pressed(SDL_SCANCODE_W)) {
            dir.y -= 1;
            sprite_offset.y = 1;
        }
    
        if (input::is_key_pressed(SDL_SCANCODE_S)) {
            dir.y += 1;
            sprite_offset.y = 0;
        }
    } else if (sprite_offset.x >= 1) {
        sprite_offset = {0, 0};
    }

    if (dir.x == 0 && dir.y == 0 && !actioned) return;

    uint32_t idx = map::find_cluster_idx(get_position());
    std::vector<cluster *> m_clusters = map::get_surrounding_clusters(idx);

    if (actioned) {
        interactible *cc = map::perceive(this, m_clusters);

        if (cc != nullptr) {
            cc->interact(this);
            sprite_offset.y = 4;
        };
    }

    if (dir.x == 0 && dir.y == 0) return;

    vec2<float> dposx = {{dir.x * speed * dt, 0}};
    vec2<float> dposy = {{0, dir.y * speed * dt}};

    bool colx = physics::check_collide(this, dposx, m_clusters);
    bool coly = physics::check_collide(this, dposy, m_clusters);

    if (!colx) move(dposx.x, 0);
    if (!coly) move(0, dposy.y);

    if (!(colx && coly)) {
        unsigned int new_idx = map::find_cluster_idx(get_position());
        map::clusters[idx].foreground.erase(this);
        map::clusters[new_idx].foreground.insert(this);
        if (idx != new_idx) {
            map::clusters[idx].collidables.erase(this);
            map::clusters[new_idx].collidables.insert(this);
        }
    }
}

void player::damage(float damage_value) {
    current_health = std::max(current_health - damage_value, 0.f);
}

void player::heal(float heal_value) { current_health = std::min(heal_value + current_health, max_health); }

float player::get_max_health() const { return max_health; }
float player::get_current_health() const { return current_health; }


void player::lose_food(float lose_value) {
    current_food = std::max(current_food - lose_value, 0.f);
}

void player::collect_food(float collect_value) {
    current_food = std::min(collect_value + current_food, max_food);
}

float player::get_max_food() const { return max_food; }
float player::get_current_food() const { return current_food; }

void player::lose_copper(float lose_value) {
    current_copper = std::max(current_copper - lose_value, 0.f);
}

void player::collect_copper(float collect_value) {
    current_copper = std::min(collect_value + current_copper, max_copper);
}

float player::get_max_copper() const {
    return max_copper;
}

float player::get_current_copper() const {
    return current_copper;
}
