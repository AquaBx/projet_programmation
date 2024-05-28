//
// Created by tomch on 27/05/2024.
//

#include "sprite.h"
#include <cstdlib>
#include <iostream>

#include "renderer.h"

sprite::sprite(const char * src, vec2<float> position, vec2<float> size, vec2<int> frame_resolution, const std::vector<int>& max_frames):
    image_src(src),size(size), frame_resolution(frame_resolution), position(position), max_frames(max_frames)
{

}

void sprite::draw() const {
    renderer::draw_texture(position,size,frame_resolution,texture,get_frame());
}

sprite::~sprite() {
    SDL_DestroyTexture(texture);
}

void sprite::update(float dt)
{
    frame_x += dt;

    if (frame_x > static_cast<float>(max_frames[frame_y])) {
        frame_x -= static_cast<float>(max_frames[frame_y]);
    }
}


void sprite::set_frame_y(int frame){
    frame_y = frame;
}

void sprite::set_frame_x(int frame){
    frame_x = frame;
}

int sprite::load_texture(const char * image_src) {
    return renderer::load_texture(image_src,this);
}

void sprite::set_texture(SDL_Texture* texture){
    this->texture = texture;
}

vec2<int> sprite::get_frame() const{
    vec2<int> ret_vec;
    ret_vec.x = static_cast<int>(frame_x);
    ret_vec.y = static_cast<int>(frame_y);

    return ret_vec;
}