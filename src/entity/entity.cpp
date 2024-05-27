//
// Created by cejosso on 27/05/2024.
//
#include "entity.h"

entity::entity(float x, float y, float width, float height)
        : position({x, y}), size({width, height}) {}

entity::~entity(){}

void entity::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void entity::move_to(float x, float y) {
    position.x = x;
    position.y = y;
}

vec2 entity::get_position() const {
    return this->position;
}

vec2 entity::get_size() const {
    return this->size;
}

const aabb & entity::get_collide_box() const {
    return collide_box;
}

