//
// Created by malo1 on 5/27/2024.
//

#pragma once


#include <set>
#include "entity/entity.h"
#include "entity/interactible.h"

struct compare {
    bool operator()(const entity* a, const entity* b) const {
        return a->get_position().y < b->get_position().y;
    }
};

class cluster {
private:
    aabb collision_box;

public:
    std::set<entity*, compare> entities;
    std::set<interactible*, compare> interactibles;
    //movables?

    explicit cluster(const aabb& _collide_box);

    const aabb& get_collision_box() const;
};
