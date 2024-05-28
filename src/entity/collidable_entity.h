//
// Created by malo1 on 5/28/2024.
//

#pragma once


#include "entity.h"
#include "physics/collidable.h"

class collidable_entity: public collidable, public virtual entity {
protected:
    aabb collide_box;
public:
    collidable_entity(vec2<float> pos, aabb _collide_box);

    aabb get_collide_box() const override;
};
