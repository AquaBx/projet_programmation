//
// Created by celia on 27/05/2024.
//
#pragma once

#include <cstdint>

#include "physics/circle.h"
#include "animated_sprite.h"
#include "collidable_entity.h"

class player : public animated_sprite, public collidable_entity {
protected:
    const float max_health;
    float current_health;
    const float max_food;
    float current_food;
    const float max_copper;
    float current_copper;

public:
    uint32_t tick;

public :
    player(vec2<float> pos, vec2<float> size, float max_health, float max_food, float max_copper);

    void update(float dt) override;
    void draw(const camera &cam) const override;

    void damage(float damage_value);
    void heal(float heal_value);

    float get_max_health() const;

    float get_current_health() const;

    void collect_food(float collect_value);

    void lose_food(float lose_value);

    float get_max_food() const;
    float get_current_food() const;

    void collect_copper(float collect_value);

    void lose_copper(float lose_value);

    float get_max_copper() const;

    float get_current_copper() const;

    circle get_interact_zone() const;

};
