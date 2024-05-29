//
// Created by tomch on 29/05/2024.
//

#pragma once
#include "crop.h"
#include "interactible.h"


class wheat_crop: public crop
{
public:
    wheat_crop(vec2<float> pos, vec2<float> size):
entity(pos),crop(pos,size,0){}
};
