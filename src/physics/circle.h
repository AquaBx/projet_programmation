//
// Created by tomch on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"

struct circle {
    float rayon;
    vec2<float> position;
};

inline circle operator+ (const circle& old, const vec2<float> & dpos){
    circle nouveau{};
    nouveau.rayon = old.rayon;
    nouveau.position = old.position + dpos;

    return nouveau;
}