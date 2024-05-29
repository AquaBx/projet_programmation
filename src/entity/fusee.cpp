//
// Created by tomch on 29/05/2024.
//

#include "fusee.h"

#include <algorithm>
#include "renderer.h"


fusee::fusee(vec2<float> pos, vec2<float> size, float max_health) :
        entity(pos),
        animated_sprite(pos, size, {{48, 48}}, {{size.x / 2, size.y / 2}}, "../resources/fusee.png", {1, 1, 2, 2, 2}, 0.1),
        collidable_entity(pos, aabb{20, 39, 41, 9}),
        interactible(24, 30, 20),
        max_health(max_health), current_health(0.f) {
}

void fusee::draw(const camera &cam) const {
    vec4<float> transformed = cam.transform({{position.x + 8, position.y + 4}}, {{33 * std::min(1.f, (current_health / max_health)), 3}});
    renderer::draw_rect(transformed.x, transformed.y, transformed.width, transformed.height,
                        renderer::color{210, 132, 86, 255});
    sprite::draw(cam);
}

circle fusee::get_interact_zone() const {
    return interactible::get_interact_zone() + get_position();
}

void fusee::update(float dt) {
    animated_sprite::update(dt);
}

void fusee::benefit(float benefit_value) {
    current_health = std::min(benefit_value + current_health, max_health);
}

float fusee::get_max_health() const {
    return max_health;
}

float fusee::get_current_health() const {
    return current_health;
}

void fusee::interact(player *user)  {
    benefit(1.f);
    user->damage(5.f);
    uint32_t idx = std::min(4, 1+(int)(3*(current_health/max_health)));
    sprite_offset = {{0, idx}};
    if(current_health >= max_health) {
        // TODO victoire
    }
}
