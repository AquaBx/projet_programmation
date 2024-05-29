//
// Created by tomch on 27/05/2024.
//

#include "aabb.h"
#include "physics.h"

#include <iostream>

#include "cluster.h"
// #include "entity/collidable.h"

bool physics::are_colliding(const aabb &collide_1, const aabb &collide_2) {
    bool c1 = collide_1.right < collide_2.left;
    bool c2 = collide_1.left > collide_2.right;
    bool c3 = collide_1.top > collide_2.bottom;
    bool c4 = collide_1.bottom < collide_2.top;

    return !(c1 || c2 || c3 || c4);
}

float physics::shared_distance(const circle &collide_1, const circle &collide_2) {
    float r = (collide_1.rayon + collide_2.rayon);
    float d = collide_1.position.distance(collide_2.position);
    float c = r - d;
    return std::max(0.0f, c);
}

bool
physics::check_collide(const collidable *entity_collide, vec2<float> dpos, const std::vector<cluster *> &clusters) {
    for (cluster *clus: clusters) {
        for (collidable *coll: clus->collidables) {
            if (coll != entity_collide && are_colliding(entity_collide->get_collide_box() + dpos,
                                                        coll->get_collide_box())) {
                return true;
            }
        }
    }
    return false;
}
