//
// Created by tomch on 28/05/2024.
//
#pragma once

#include "physics/circle.h"
#include <cstdint>
#include <iostream>

#include "animated_sprite.h"
#include "collidable_entity.h"
#include "interactible.h"
#include "pnj.h"

class cow : public pnj {
protected:
    float max_delai_interact = 2.0f;
    float delai_interact = max_delai_interact;

public :
    cow(vec2<float> pos, vec2<float> size, float max_health);

    void update(float dt) override;

    void damage(float damage_value);
    void heal(float benefit_value);

    float get_max_health() const;
    float get_current_health() const;

    void interact(player* user) override;
};
