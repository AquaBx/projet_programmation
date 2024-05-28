//
// Created by celia on 27/05/2024.
//
#pragma once

#include "camera.h"
#include "gui_component.h"
#include "entity/player.h"

class health_bar : public gui_component {
public :
    health_bar(vec2<float> _position, vec2<float> _size, vec2<int> _sprite_offset , vec2<int> _sprite_resolution, const char* image_src, player * p);

    void draw(const camera& cam) const override;
    void update(float dt) override;

private:
    const player * p;
    float current_health;
    float max_health;
};