//
// Created by tomch on 27/05/2024.
//

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "utils/vec2.h"

class sprite {
protected:
    SDL_Texture* texture;
    const char * image_src;
    vec2<float> size;
    vec2<int> frame_resolution;
    vec2<float> position;

    float frame_x = 0.0f;
    int frame_y = 0;

    std::vector<int> max_frames;
public:

    int get_number_of_animation();

    int load_texture();

    sprite(const char * src, vec2<float> position, vec2<float> size, vec2<int> frame_resolution, std::vector<int> max_frames) : image_src(src),position(position), size(size), frame_resolution(frame_resolution), max_frames(max_frames) {}

    void set_texture(SDL_Texture* texture);

    void draw() const;

    void update(float dt);

    ~sprite();

    vec2<int> get_frame() const;
};