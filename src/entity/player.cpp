//
// Created by celia on 27/05/2024.
//
#include <algorithm>
#include <iostream>

#include "player.h"

#include "cluster.h"
#include "renderer.h"

#include "input.h"
#include "map/map.h"
#include "physics/physics.h"

player::player(vec2<float> pos, vec2<float> size, float max_health):
    entity(pos),
    animated_sprite(pos, size, {{48, 48}}, "../resources/player.png", {4}, 0.1),
    collidable_entity(pos, aabb{24, 28, 32, 20}),
    max_health(max_health), current_health(max_health)
{
}

void player::draw(const camera& cam) const
{
    collidable_entity::draw_collide_box(cam);
    sprite::draw(cam);
}

circle player::get_interact_zone() const
{
    circle interact_zone{8, size / 2.0f};
    return interact_zone + get_position();
}

void player::update(float dt){
    animated_sprite::update(dt);
    damage(dt);

    bool actioned = input::is_key_pressed(SDL_SCANCODE_E);


    vec2<float> dir{{0, 0}};

    if (input::is_key_pressed(SDL_SCANCODE_A)) { dir.x -= 1; }
    if (input::is_key_pressed(SDL_SCANCODE_D)) { dir.x += 1; }
    if (input::is_key_pressed(SDL_SCANCODE_W)) { dir.y -= 1; }
    if (input::is_key_pressed(SDL_SCANCODE_S)) { dir.y += 1; }
    const float speed = 50;

    if (dir.x == 0 && dir.y == 0 && !actioned) return;

    uint32_t idx = map::find_cluster_idx(get_position());
    std::vector<cluster*> m_clusters = map::get_surrounding_clusters(idx);

    if (actioned)
    {
        interactible* cc = map::perceive(this, m_clusters);

        if (cc != nullptr) cc->interact(this);
    }

    if (dir.x == 0 && dir.y == 0) return;

    vec2<float> dposx = {{dir.x * speed * dt, 0}};
    vec2<float> dposy = {{0, dir.y * speed * dt}};

    bool colx = physics::check_collide(this, dposx, m_clusters);
    bool coly = physics::check_collide(this, dposy, m_clusters);

    if (!colx) move(dposx.x, 0);
    if (!coly) move(0, dposy.y);

    if(!(colx && coly)) {
        unsigned int new_idx = map::find_cluster_idx(get_position());
        map::clusters[idx].foreground.erase(this);
        map::clusters[new_idx].foreground.insert(this);
        if(idx != new_idx) {
            map::clusters[idx].collidables.erase(this);
            map::clusters[new_idx].collidables.insert(this);
        }
    }
}

void player::damage(float damage_value)
{
    current_health = std::max(current_health - damage_value, 0.f);
}

void player::benefit(float benefit_value)
{
    current_health = std::min(benefit_value + current_health, max_health);
}

int player::get_max_health() const
{
    return max_health;
}

int player::get_current_health() const
{
    return current_health;
}
