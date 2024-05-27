//
// Created by tomch on 27/05/2024.
//

#include "physics.h"
// #include "entity/collidable.h"

void physics::check_and_collide( collidable & m_entity, const aabb & collide_box) {
    aabb entity_box /* = m_entity.get_collide_box()*/;

    float mx = 0;
    float my = 0;

    if ( collide_box.left < entity_box.left && entity_box.left < collide_box.right ) {
        mx = collide_box.right - entity_box.left;
    }
    else if ( collide_box.left < entity_box.right && entity_box.right < collide_box.right ){
        mx = collide_box.left - entity_box.right;
    }

    if ( collide_box.top < entity_box.bottom && entity_box.bottom < collide_box.bottom ) {
        my = collide_box.top - entity_box.bottom;
    }
    else if ( collide_box.top < entity_box.top && entity_box.top < collide_box.bottom ){
        my = collide_box.bottom - entity_box.top;
    }

    // m_entity.move(mx, my);
}

void physics::check_and_collide(collidable & m_entity, const std::vector<aabb> & collidables){
    for (aabb collidable : collidables) {
        check_and_collide(m_entity,collidable);
    }
}