//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "utils/vec2.h"
#include "animated_sprite.h"
#include "collidable_entity.h"
#include "interactible.h"

class pnj : public animated_sprite, public collidable_entity, public interactible {

protected:
    vec2<float> position_initiale;
    vec2<float> objectif;
    const float max_health;
    float current_health;

    uint32_t tick;

public:

    pnj(vec2<float> pos, vec2<float> size, float _max_health, aabb collide_box, vec2<uint32_t> frame_res,
        const char *image_src, std::vector<uint32_t> animation_lengths);

    void update(float dt) override;

    void damage(float damage_value);

    void heal(float benefit_value);

    float get_max_health() const;

    float get_current_health() const;

    circle get_interact_zone() const override;

    void draw(const camera &cam) const override;
};
