//
// Created by malo1 on 5/27/2024.
//

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"
#include "context.h"
#include "renderer.h"

context::context(unsigned int _width, unsigned int _height)
        : width(_width), height(_height), window(nullptr) {
    if (auto code = SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error(code: " << code << ") on SDL_Init with code " << code << " : " << SDL_GetError()
                  << std::endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Jeu ESIR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) _width,
                                    (int) _height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error on SDL_CreateWindow : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (!renderer::initialize(this->window)) {
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(1);
    }

    input::initialize();
}

context::~context() {
    IMG_Quit();
    renderer::terminate();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
