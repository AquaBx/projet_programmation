//
// Created by malo1 on 5/27/2024.
//

#pragma once


#include "entity/entity.h"

class camera {
protected:
    float x, y, width, height;
    float inner_x, inner_y, inner_width, inner_height;
    aabb outer_range;
    const entity* reference;
public:
    camera(float _x, float _y, float _width, float _height, float free_move_ratio, float outer_simulation_ratio, const entity* _reference);

    void update();

    void change_reference(const entity* _reference);

    const aabb& get_outer_range();
};
