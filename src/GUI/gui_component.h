//
// Created by celia on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"
#include <string>

#include "entity/sprite.h"

class gui_component : public sprite{
public:
    gui_component(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset , vec2<uint32_t> _sprite_resolution, const char* image_src);
};

