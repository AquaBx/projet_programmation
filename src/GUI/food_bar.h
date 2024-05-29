//
// Created by celia on 29/05/2024.
//

#pragma once

#include "camera.h"
#include "gui_component.h"
#include "entity/player.h"

class food_bar : public gui_component
{
public :
    food_bar(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset, vec2<uint32_t> _sprite_resolution,
             const char* image_src, player* p);

    void draw(const camera& cam) const override;
    void update(float dt) override;

private:
    const player* p;
    float current_food;
    float max_food;
};
