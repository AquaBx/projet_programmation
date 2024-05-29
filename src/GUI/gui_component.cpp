//
// Created by celia on 27/05/2024.
//

#include "gui_component.h"

gui_component::gui_component(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset,
                             vec2<uint32_t> _sprite_resolution, const char *image_src)
        : entity(_position), sprite(_position, _size, _sprite_offset, _sprite_resolution, {{0, 0}}, image_src) {}