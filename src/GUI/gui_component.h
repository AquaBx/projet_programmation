//
// Created by celia on 27/05/2024.
//
#pragma once

#include "utils/vec2.h"
#include <string>

class gui_component {
public:
    gui_component(const float x, const float y, const float width, const float height);
    virtual ~gui_component();

    virtual void draw() = 0;
    virtual void update(float dt) = 0;

protected:
    vec2 position;
    vec2 size;
};

