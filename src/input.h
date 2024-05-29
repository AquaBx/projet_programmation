//
// Created by malo1 on 5/28/2024.
//

#pragma once


#include "SDL_scancode.h"

namespace input {

    void initialize();

    bool is_key_pressed(SDL_Scancode scancode);

} //namespace input
