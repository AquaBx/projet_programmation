//
// Created by tomch on 29/05/2024.
//

#include "chicken.h"

chicken::chicken(vec2<float> pos, vec2<float> size, float max_health) :
        entity(pos),
        pnj(pos, size, max_health, aabb{8, 16, 16, 0}, {{16, 16}}, "../resources/chicken.png", {2, 4}) {}

void chicken::update(float dt) {
    pnj::update(dt);

    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 0;
    } else {
        delai_interact += dt;
    }
}