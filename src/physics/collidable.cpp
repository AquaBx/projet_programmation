//
// Created by tomch on 28/05/2024.
//

#include "collidable.h"

collidable::collidable(float top, float bottom, float left, float right)
    : collide_box{top,right,bottom,left} {}

const aabb & collidable::get_collide_box() const{
    return collide_box;
}