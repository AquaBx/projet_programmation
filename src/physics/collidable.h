//
// Created by tomch on 28/05/2024.
//

#pragma once

#include "aabb.h"

class collidable {
protected:
    aabb collide_box;
public :
    collidable(float top, float bottom, float left, float right);
    ~collidable() = default;
    const aabb & get_collide_box() const;
};