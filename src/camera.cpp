//
// Created by malo1 on 5/27/2024.
//

#include "camera.h"
#include <cassert>
#include <algorithm>

camera::camera(float _x, float _y, float _width, float _height, float _free_move_ratio, const entity* _reference):
    x(_x), y(_y), width(_width), height(_height),
    inner_x(_width*(1.f-_free_move_ratio)/2.f), inner_y(_height*(1.f-_free_move_ratio)/2.f),
    inner_width(_width * _free_move_ratio), inner_height(_height * _free_move_ratio),
    reference(_reference)
{
    assert(0.f < _free_move_ratio && _free_move_ratio <= 1.f);
}

void camera::update() {
    vec2 ref_pos = reference->get_position();
    this->x -= std::max(0.f, (x+inner_x) - ref_pos.x); //left
    this->x += std::max(0.f, (ref_pos.x + reference->get_size().width) - (x + inner_x + inner_width)); //right
    this->y -= std::max(0.f, (y+inner_y) - ref_pos.y); //top
    this->y += std::max(0.f, (ref_pos.y + reference->get_size().height) - (y + inner_y + inner_height)); //bottom
}

void camera::change_reference(const entity* _reference) { this->reference = _reference; }
