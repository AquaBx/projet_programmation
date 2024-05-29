//
// Created by tomch on 28/05/2024.
//

#include "cow.h"

#include <algorithm>
#include "renderer.h"
#include "map/map.h"


cow::cow(vec2<float> pos, vec2<float> size, float max_health) :
        entity(pos),

        pnj(pos, size, max_health, aabb{24, 24, 32, 8}, {{32, 32}}, "../resources/cow.png", {3, 3, 2}) {
}

void cow::update(float dt) {
    pnj::update(dt);

    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 0;
    } else {
        delai_interact += dt;
    }
}

void cow::interact(player *user) {
    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 1;
        delai_interact = 0;
        user->heal(10.f);
    }
}