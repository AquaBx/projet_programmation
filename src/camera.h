//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include "config.h"
#include "utils/vec4.h"
#include "entity/entity.h"

// forward declaration of #include "entity/sprite.h"
class sprite;

class camera {
//protected:
public:
    vec2<float> pos, size, inner_pos, inner_size;
    float outer_simulation_ratio;
    const sprite *reference = nullptr;

public:
    camera() = default;

    camera(vec2<float> _pos, vec2<float> _size, float free_move_ratio, float outer_simulation_ratio,
           const sprite *_reference);

    void update();

    void change_reference(const sprite *_reference);

    aabb get_outer_range() const;

    vec4<float> transform(vec2<float> _position, vec2<float> _size) const {
        return {{
                        (_position.x - pos.x) * config::ratio.x,
                        (_position.y - pos.y) * config::ratio.y,
                        _size.width * config::ratio.x,
                        _size.height * config::ratio.y,
                }};
    }
};
