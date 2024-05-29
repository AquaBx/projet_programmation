//
// Created by tomch on 29/05/2024.
//

#pragma once

#include "crop.h"
#include "interactible.h"


class copper : public crop, public sprite{

    public:
        copper(vec2<float> pos, vec2<float> size) :
                entity(pos), crop(pos, size, 2),
                sprite(pos, {{18,17}}, {{0, 0}}, {{18, 17}}, {{size.x / 2, size.y / 2}},
                "../resources/copper.png"){}

                void interact(player *user) override;
                void update(float dt);
};