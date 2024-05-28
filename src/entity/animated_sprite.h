//
// Created by malo1 on 5/28/2024.
//

#pragma once


#include "sprite.h"
#include <vector>

class animated_sprite: public sprite {
protected:
    float time;
    const float frame_time;
    std::vector<int> animation_lengths;
public:
    animated_sprite(vec2<float> _position, vec2<float> _size, vec2<int> _frame_resolution, const char* image_src, const std::vector<int>& _animation_lengths, float _frame_time, int animation_id = 0);

    void update(float dt) override;
};
