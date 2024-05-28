//
// Created by cejosso on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"
#include "physics/aabb.h"

class entity {
public:
    entity(float x, float y, float width, float height);

    virtual ~entity();

    virtual void draw() = 0;
    virtual void update(float dt) = 0;

    void move(float dx, float dy);
    void move_to(float x, float y);

    vec2<float> get_position() const;
    vec2<float> get_size() const;

protected :
    vec2<float> position;
    vec2<float> size;
};
