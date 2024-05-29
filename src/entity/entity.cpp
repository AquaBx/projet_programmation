//
// Created by cejosso on 27/05/2024.
//
#include "entity.h"

entity::entity(vec2<float> _position)
        : position(_position) {
}

entity::~entity() = default;

void entity::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void entity::move_to(float x, float y) {
    position.x = x;
    position.y = y;
}

vec2<float> entity::get_position() const {
    return this->position;
}
