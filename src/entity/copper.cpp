//
// Created by tomch on 29/05/2024.
//

#include "copper.h"

void copper::interact(player * user){
    if (age >= 1) {
        user->damage(10);
        user->collect_copper(10);
        age = 0;
    }
}

void copper::update(float dt) {
    age += dt / 2;
    sprite::sprite_offset.x = std::min(1, static_cast<int>(age));
    sprite::update(dt);
}

circle copper::get_interact_zone() const {
    return interactible::get_interact_zone() + get_position();
}

void copper::draw(const camera &cam) const {
    //interactible::draw_interact_zone(cam, position);
    sprite::draw(cam);
}
