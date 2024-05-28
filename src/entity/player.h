//
// Created by celia on 27/05/2024.
//
#pragma once

#include "physics/circle.h"
#include <cstdint>
#include "animated_sprite.h"
#include "collidable_entity.h"

class player : public animated_sprite, public collidable_entity
{
protected:
    const float max_health;
    float current_health;

public :
    player(vec2<float> pos, vec2<float> size, float max_health);
    void update(float dt) override;
    void damage(float damage_value);
    void benefit(float benefit_value);
    int get_max_health() const;
    int get_current_health() const;
    circle get_interact_zone() const;

    void draw(const camera & cam) const override;
};
