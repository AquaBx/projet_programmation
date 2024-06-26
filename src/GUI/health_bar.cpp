//
// Created by celia on 27/05/2024.
//

#include "health_bar.h"
#include "renderer.h"

health_bar::health_bar(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset,
                       vec2<uint32_t> _sprite_resolution, const char *image_src, player *p)
        : entity(_position), gui_component(_position, _size, _sprite_offset, _sprite_resolution, image_src), p(p),
          current_health(100.0f), max_health(p->get_max_health()) {}

void health_bar::draw(const camera& cam) const {
    float health_width = (current_health / max_health) * 89;

    renderer::draw_rect(position.x + 28, position.y + 7, health_width, 9, renderer::colors::red);
    renderer::draw_texture({{position.x, position.y}}, {{size.width, size.height}},sprite_resolution, texture, sprite_offset);
}

void health_bar::update(float dt) {
    current_health = p->get_current_health();
}

