//
// Created by tomch on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"

struct aabb {
    float top, right, bottom, left;
};

inline aabb operator+ (const aabb& old, const vec2 & dpos){
    aabb nouveau{};
    nouveau.top = old.top + dpos.y;
    nouveau.bottom = old.bottom + dpos.y;
    nouveau.left = old.left + dpos.x;
    nouveau.right = old.right + dpos.x;

    return nouveau;
}