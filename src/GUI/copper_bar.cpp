//
// Created by celia on 29/05/2024.
//

#include "copper_bar.h"
#include "renderer.h"

copper_bar::copper_bar(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset,
                   vec2<uint32_t> _sprite_resolution, const char *image_src, player *p)
        : entity(_position), gui_component(_position, _size, _sprite_offset, _sprite_resolution, image_src), p(p),
          current_copper(0.0f), max_copper(p->get_max_copper()) {
}

void copper_bar::draw(const camera &cam) const {
    float food_width = (current_copper / max_copper) * (30 * 3);


    renderer::draw_rect(position.x + 9 * 3, position.y + 2 * 3, food_width, 3 * 3, renderer::colors::beige);
    renderer::draw_texture({position.x, position.y}, {size.width, size.height}, sprite_resolution, texture,
                           sprite_offset);
}

void copper_bar::update(float dt) {
    current_copper = p->get_current_copper();
}
