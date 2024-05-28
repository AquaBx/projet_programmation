//
// Created by celia on 27/05/2024.
//
#pragma once

#include "entity.h"
#include "physics/circle.h"
#include <cstdint>

#include "physics/collidable.h"

class player : public entity, public collidable {
protected:
    const uint32_t max_health;
    uint32_t current_health;
public :
    player(float x, float y, float width, float height, int max_health);
    virtual ~player() override;
    virtual void draw() override;
    virtual void update(float dt) override;
    void damage(int damage_value);
    void benefit(int benefit_value);
    int get_max_health() const;
    int get_current_health() const;
    const circle get_interact_zone() const;

    const aabb get_collide_box() const;
};
