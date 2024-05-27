//
// Created by malo1 on 5/27/2024.
//

#pragma once

#include <cmath>


union vec2 {
    struct {
        float x, y;
    };
    struct {
        float width, height;
    };

    float distance(const vec2 & other) const {
        return (float)sqrt(pow(this->x-other.x, 2) + pow(this->y-other.y, 2));
    }
};
