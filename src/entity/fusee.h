//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "animated_sprite.h"
#include "collidable_entity.h"
#include "interactible.h"


class fusee : public animated_sprite, public collidable_entity, public interactible {
protected:
    const float max_health;
    float current_health;

public :
    fusee(vec2<float> pos, vec2<float> size, float max_health);

    void update(float dt) override;

    void damage(float damage_value);

    void heal(float heal_value);

    float get_max_health() const;

    float get_current_health() const;

    circle get_interact_zone() const override;

    void draw(const camera &cam) const override;

    void interact(player *user) override {
        sprite_offset.y = 1;
    }
};
