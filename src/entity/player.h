//
// Created by celia on 27/05/2024.
//
#pragma once

#include "entity.h"
#include "physics/circle.h"

class player : public entity {
protected:
    circle interact_zone;
public :
    player(float x, float y, float width, float height, float interact_r);
    virtual ~player() override;
    virtual void draw() override;
    virtual void update(float dt) override;
    const circle & get_interact_zone() const;
};
