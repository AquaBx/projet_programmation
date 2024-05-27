//
// Created by celia on 27/05/2024.
//

#include "gui_component.h"

gui_component::gui_component(const float x, const float y, const float width, const float height)
        : position({x, y}), size({width, height}) {}

gui_component::~gui_component(){};