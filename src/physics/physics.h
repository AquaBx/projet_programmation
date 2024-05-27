//
// Created by tomch on 27/05/2024.
//
#pragma once

#include <vector>

#include "aabb.h"

struct collidable;

namespace physics {

    void check_and_collide(collidable& entity, aabb const& obstacle);
    void check_and_collide(collidable& entity, std::vector<aabb> const& obstacles);

} // namespace physics
