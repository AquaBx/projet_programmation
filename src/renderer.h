//
// Created by viann on 27/05/2024.
//
#pragma once

#include <cstdint>

#include "color.h"
#include "SDL2/SDL.h"
#include "entity/sprite.h"

namespace renderer
{
    bool initialize(void* window);
    void terminate();

    void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);
    void present();

    void draw_rect(float x, float y, float width, float height, color c = colors::black);
    void draw_texture(float x, float y, float width, float height, const char* filepath);

    void draw_texture(vec2<float> position, vec2<float> size, vec2<uint32_t> resolution, SDL_Texture* texture, vec2<uint32_t> frame);

    SDL_Texture* create_sdl_texture(const char* filepath);
    int load_texture(const char * image_src, sprite * sprite_obj);

} // namespace renderer
