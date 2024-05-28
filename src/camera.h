//
// Created by malo1 on 5/27/2024.
//

#pragma once


#include "entity/entity.h"
#include "entity/sprite.h"

class camera {
protected:
    vec2<float> pos, size, inner_pos, inner_size;
    aabb outer_range;
    const sprite* reference;
public:
    camera(vec2<float> _pos, vec2<float> _size, float free_move_ratio, float outer_simulation_ratio, const sprite* _reference);

    void update();

    void change_reference(const sprite* _reference);

    const aabb& get_outer_range() const;
};
