//
// Created by tomch on 29/05/2024.
//

#include "crop.h"

crop::crop(vec2<float> pos, vec2<float> size, uint32_t y_offset) :
        entity(pos),

        sprite(pos, size, {{1, static_cast<uint32_t>(y_offset)}}, {{16, 16}}, {{size.x / 2, size.y / 2}},
               "../resources/plants.png"),
        interactible(8, 8, 16) {}

void crop::update(float dt) {
    age += dt / 2;
    sprite_offset.x = std::min(3, static_cast<int>(age)) + 1;
    sprite::update(dt);
}

circle crop::get_interact_zone() const {
    return interactible::get_interact_zone() + get_position();
}

void crop::draw(const camera &cam) const {
    //interactible::draw_interact_zone(cam, position);
    sprite::draw(cam);
}

void crop::interact(player * user){
    if (age >= 3) {
        user->collect_food(10);
        age = 0;
    }
}
