//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "crop.h"
#include "interactible.h"


class copper : public sprite, public interactible {
protected:
    float age = 0;
public:
copper(vec2<float> pos, vec2<float> size):
    entity(pos),
    sprite(pos, {{18,17}}, {{0, 0}}, {{18, 17}}, {{size.x / 2, size.y / 2}}, "../resources/copper.png"),
    interactible(8, 8, 16)

{}

void interact(player *user) override;
void update(float dt) override;
void draw(const camera &cam) const override;
circle get_interact_zone() const override;

};