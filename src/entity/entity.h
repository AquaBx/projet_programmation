//
// Created by cejosso on 27/05/2024.
//
#pragma once


#include "utils/vec2.h"
#include "physics/aabb.h"

class entity {
public :
    entity(float x, float y, float width, float height);

    virtual ~entity();

    virtual void draw() = 0;
    virtual void update(float dt) = 0;

    void move(float dx, float dy);
    void move_to(float x, float y);

    vec2 get_position() const;
    vec2 get_size() const;

    const aabb & get_collide_box() const;

protected :
    vec2 position;
    vec2 size;
    aabb collide_box;
};
