//
// Created by celia on 27/05/2024.
//
#include <algorithm>
#include "player.h"
#include "renderer.h"

player::player(float x, float y, float width, float height, int max_health)
        : entity(x, y, width, height), collidable(0,0,0,0), max_health(max_health), current_health(max_health)    {
}

const aabb &player::get_collide_box() const {
    return collide_box + get_position();
}

const circle & player::get_interact_zone() const{
    circle interact_zone{15,size/2.0f};
    return interact_zone + get_position();
}

player::~player(){}

void player::draw(){
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);
}

void player::update(float dt){
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
