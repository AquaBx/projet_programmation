//
// Created by malo1 on 5/28/2024.
//

#include "collidable_entity.h"

collidable_entity::collidable_entity(vec2<float> pos, aabb _collide_box):
        entity(pos),
        collide_box(_collide_box)
{}

aabb collidable_entity::get_collide_box() const {
    return this->collide_box + get_position();
}
