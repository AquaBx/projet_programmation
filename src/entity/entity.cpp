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
