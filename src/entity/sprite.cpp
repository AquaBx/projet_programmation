//
// Created by malo1 on 5/28/2024.
//

#include "sprite.h"
#include "renderer.h"

sprite::sprite(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset,
               vec2<uint32_t> _sprite_resolution, vec2<float> _anchor, const char *image_src) :
        entity(_position), size(_size), sprite_offset(_sprite_offset), sprite_resolution(_sprite_resolution),
        anchor(_anchor) {
    renderer::load_texture(image_src, this);
}

void sprite::set_texture(SDL_Texture *_texture) {
    this->texture = _texture;
}

vec2<float> sprite::get_size() const {
    return this->size;
}

void sprite::draw(const camera &cam) const {
    vec4<float> transformed = cam.transform(position, size);
    renderer::draw_texture({{transformed.x, transformed.y}}, {{transformed.width, transformed.height}},
                           sprite_resolution, texture, sprite_offset);

}

vec2<float> sprite::get_anchored_pos() const {
    return this->get_position() + this->anchor;
}
