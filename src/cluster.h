//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <set>
#include <vector>
#include <unordered_set>

#include "entity/sprite.h"
#include "entity/interactible.h"

#include "physics/collidable.h"

struct y_sort {
    bool operator()(const sprite* a, const sprite* b) const {
        return (a != b) && ((a->get_anchored_pos().y == b->get_anchored_pos().y && a < b) || (a->get_anchored_pos().y < b->get_anchored_pos().y));
    }
};

class cluster {
private:
    aabb collision_box;

public:
    std::vector<sprite*> background;
    std::set<sprite*, y_sort> foreground;
    std::unordered_set<collidable*> collidables;
    std::unordered_set<interactible*> interactibles;

    explicit cluster(const aabb& _collide_box);

    const aabb& get_collision_box() const;
};
