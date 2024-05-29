//
// Created by malo1 on 5/27/2024.
//

#include "cluster.h"

cluster::cluster(const aabb &_collide_box) : collision_box(_collide_box) {

}

const aabb &cluster::get_collision_box() const {
    return this->collision_box;
}
