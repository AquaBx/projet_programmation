//
// Created by tomch on 27/05/2024.
//
#pragma once

#include <vector>

#include "aabb.h"
#include "circle.h"
#include "collidable.h"

namespace physics {

    bool are_colliding(const aabb & collide_1,const aabb & collide_2);
    float shared_distance(const circle & collide_1,const circle & collide_2);

    bool check_collide(const aabb & entity_collide, std::vector<aabb> const& obstacles);

} // namespace physics
