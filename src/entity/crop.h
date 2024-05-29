//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "interactible.h"
#include "sprite.h"

class crop : public sprite, public interactible {
protected:
    float age = 0;

public :
    crop(vec2<float> pos, vec2<float> size, uint32_t y_offset);

    void update(float dt) override;

    circle get_interact_zone() const override;

    void draw(const camera &cam) const override;

    void interact(player *user) override;
};
