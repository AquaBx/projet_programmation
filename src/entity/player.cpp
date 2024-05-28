//
// Created by celia on 27/05/2024.
//
#include <algorithm>
#include "player.h"
#include "renderer.h"

player::player(vec2<float> pos, vec2<float> size, int max_health):
        entity(pos),
        animated_sprite(pos, size, {{48, 48}}, "../resources/test.bmp", {4}, 0.1),
        collidable_entity(pos, aabb{0.f, 0.f, size.width, size.height}),
        max_health(max_health), current_health(max_health)
{}


const circle player::get_interact_zone() const{
    circle interact_zone{15,size/2.0f};
    return interact_zone + get_position();
}

void player::update(float dt) {
    animated_sprite::update(dt);
    const float speed = 10;
    move(speed * dt, 0);
}

void player::damage(int damage_value) {
    current_health = std::max(current_health-damage_value, static_cast<uint32_t>(0));
}

void player::benefit(int benefit_value) {
    current_health = std::min(benefit_value + current_health, max_health);
}

int player::get_max_health() const {
    return max_health;
}

int player::get_current_health() const {
    return current_health;
}
