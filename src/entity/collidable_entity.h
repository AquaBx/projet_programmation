//
// Created by malo1 on 5/28/2024.
//

#pragma once


#include "entity.h"
#include "physics/collidable.h"
#include "utils/vec4.h"

class collidable_entity : public collidable, public virtual entity {
protected:
    aabb collide_box;

public:
    collidable_entity(vec2<float> pos, aabb _collide_box);

    aabb get_collide_box() const override;

    void draw_collide_box(const camera &cam) const {
        aabb abs = collide_box + position;

        vec4<float> monrect = cam.transform({{abs.left, abs.top}}, {{abs.right - abs.left, abs.bottom - abs.top}});

        renderer::draw_rect(monrect.x, monrect.y, monrect.width, monrect.height);
    }
};
