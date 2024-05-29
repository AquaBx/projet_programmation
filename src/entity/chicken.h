//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "physics/circle.h"
#include <cstdint>
#include <iostream>

#include "animated_sprite.h"
#include "collidable_entity.h"
#include "interactible.h"
#include "pnj.h"

class chicken : public pnj {
protected:
    float max_delai_interact = 2.0f;
    float delai_interact = max_delai_interact;

public :
    chicken(vec2<float> pos, vec2<float> size, float max_health);

    void update(float dt) override;

    void interact(player *user) override {

    };
};
