//
// Created by celia on 27/05/2024.
//
#pragma once

#include "physics/circle.h"
#include <cstdint>
#include "animated_sprite.h"
#include "collidable_entity.h"

class player : public animated_sprite, public collidable_entity {
protected:
    const float max_health;
    float current_health;
    const float max_food;
    float current_food;

    uint32_t tick;
public :
    player(vec2<float> pos, vec2<float> size, float max_health, float max_food);

    void update(float dt) override;

    void damage(float damage_value);

    void benefit(float benefit_value);

    float get_max_health() const;

    float get_current_health() const;

    void collect(float collect_value);

    void lose(float lose_value);

    float get_max_food() const;

    float get_current_food() const;

    void collect(float collect_value);

    void lose(float lose_value);

    circle get_interact_zone() const;

    void draw(const camera &cam) const override;
};
