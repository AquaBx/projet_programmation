//
// Created by tomch on 28/05/2024.
//

#include "cow.h"

#include <algorithm>
#include "renderer.h"
#include "input.h"

cow::cow(vec2<float> pos, vec2<float> size, int max_health):
    entity(pos),
    animated_sprite(pos, size, {{32, 32}}, "../resources/cow.png", {3,3,2}, 0.1),
    collidable_entity(pos, aabb{24, 24, 32, 8}),
    interactible(16, 16, 32),
    max_health(max_health), current_health(max_health)
{
}

void cow::draw(const camera& cam) const
{
    //interactible::draw_interact_zone(cam, position);
    //collidable_entity::draw_collide_box(cam);
    sprite::draw(cam);
}

circle cow::get_interact_zone() const
{
    return interactible::get_interact_zone() + get_position();
}

void cow::update(float dt)
{
    animated_sprite::update(dt);

    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 0;
    }
    else {
        delai_interact += dt;
    }

    vec2<float> dir{{0, 0}};

    //if (input::is_key_pressed(SDL_SCANCODE_A)) { dir.x -= 1; }
    //if (input::is_key_pressed(SDL_SCANCODE_D)) { dir.x += 1; }
    //if (input::is_key_pressed(SDL_SCANCODE_W)) { dir.y -= 1; }
    //if (input::is_key_pressed(SDL_SCANCODE_S)) { dir.y += 1; }

    const float speed = 10;
    move(dir.x * speed * dt, dir.y * speed * dt);
}

void cow::damage(int damage_value)
{
    current_health = std::max(current_health - damage_value, static_cast<uint32_t>(0));
}

void cow::benefit(int benefit_value)
{
    current_health = std::min(benefit_value + current_health, max_health);
}

int cow::get_max_health() const
{
    return max_health;
}

int cow::get_current_health() const
{
    return current_health;
}
