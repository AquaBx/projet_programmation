//
// Created by tomch on 27/05/2024.
//
#pragma once

#include <vector>

#include "aabb.h"
#include "circle.h"
#include "entity/entity.h"

namespace physics {

    bool are_colliding(const aabb & collide_1,const aabb & collide_2);
    float shared_distance(const circle & collide_1,const circle & collide_2);

    void check_and_collide( entity & m_entity, const vec2 & dpos,const aabb & collide_box);
    void check_and_collide(entity& entity, const vec2 & dpos,std::vector<aabb> const& obstacles);

} // namespace physics
