//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <SDL2/SDL_render.h>

class context {
protected:
    unsigned int width, height;
    SDL_Window* window;

public:
    context(unsigned int _width, unsigned int _height);
    virtual ~context();
};
