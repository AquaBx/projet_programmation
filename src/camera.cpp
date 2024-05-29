//
// Created by malo1 on 5/27/2024.
//
#include <cassert>
#include <algorithm>

#include "camera.h"
#include "entity/sprite.h"

camera::camera(vec2<float> _pos, vec2<float> _size, float free_move_ratio, float _outer_simulation_ratio,
               const sprite *_reference) :
        pos(_pos), size(_size),
        inner_pos{{size.width * (1.f - free_move_ratio) / 2.f, size.height * (1.f - free_move_ratio) / 2.f}},
        inner_size{{size.width * free_move_ratio, size.height * free_move_ratio}},
        outer_simulation_ratio(_outer_simulation_ratio),
        reference(_reference) {
    assert(0.f < free_move_ratio && free_move_ratio <= 1.f && "free move ratio must be between 0 and 1");
//    assert(outer_simulation_ratio >= 1.f);
}

void camera::update() {
    vec2<float> ref_pos = reference->get_position();
    this->pos.x -= std::max(0.f, (pos.x + inner_pos.x) - ref_pos.x); //left
    this->pos.x += std::max(0.f, (ref_pos.x + reference->get_size().width) -
                                 (pos.x + inner_pos.x + inner_size.width)); //right
    this->pos.y -= std::max(0.f, (pos.y + inner_pos.y) - ref_pos.y); //top
    this->pos.y += std::max(0.f, (ref_pos.y + reference->get_size().height) -
                                 (pos.y + inner_pos.y + inner_size.height)); //bottom
}

void camera::change_reference(const sprite *_reference) { this->reference = _reference; }

aabb camera::get_outer_range() const {
    return {pos.y - size.height * (outer_simulation_ratio - 1) / 2,
            pos.x + size.width + size.width * (outer_simulation_ratio - 1) / 2,
            pos.y + size.height + size.height * (outer_simulation_ratio - 1) / 2,
            pos.x - size.width * (outer_simulation_ratio - 1) / 2,
    };
}
