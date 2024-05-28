//
// Created by malo1 on 5/28/2024.
//
#pragma once

#include <SDL2/SDL_render.h>

#include "camera.h"

#include "entity/entity.h"

class sprite : public virtual entity
{
protected:
    vec2<float> size;
    vec2<int> sprite_offset;
    vec2<int> sprite_resolution;
    SDL_Texture* texture = nullptr;

public:
    sprite(vec2<float> _position, vec2<float> _size, vec2<int> _sprite_offset, vec2<int> _frame_resolution,
           const char* image_src);

    vec2<float> get_size() const;

    virtual void draw(const camera& cam) const;

    void set_texture(SDL_Texture* texture);
};
