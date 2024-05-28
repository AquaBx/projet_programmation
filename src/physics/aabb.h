//
// Created by tomch on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"

struct aabb {
    float top, right, bottom, left;

    vec2<float> top_left() const {return {{left, top}};}
    vec2<float> bottom_left() const {return {{left, bottom}};}
    vec2<float> bottom_right() const {return {{right, bottom}};}
    vec2<float> top_right() const {return {{right, top}};}
    vec2<float> center() const {return {{(left+right)/2.f, (top+bottom)/2.f}};}
};

inline aabb operator+ (const aabb& old, const vec2<float> & dpos){
    aabb nouveau{};
    nouveau.top = old.top + dpos.y;
    nouveau.bottom = old.bottom + dpos.y;
    nouveau.left = old.left + dpos.x;
    nouveau.right = old.right + dpos.x;

    return nouveau;
}