//
// Created by malo1 on 5/28/2024.
//
#pragma once

#include <SDL2/SDL_render.h>

#include "camera.h"

#include "entity/entity.h"

class sprite : public virtual entity {
protected:
    vec2<float> size;
    vec2<uint32_t> sprite_offset;
    vec2<uint32_t> sprite_resolution;
    SDL_Texture *texture = nullptr;
private:
    vec2<float> anchor;
public:
    sprite(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _sprite_offset, vec2<uint32_t> _frame_resolution,
           vec2<float> _anchor, const char *image_src);

    vec2<float> get_size() const;

    virtual void draw(const camera &cam) const;

    void set_texture(SDL_Texture *texture);

    vec2<float> get_anchored_pos() const;
};
