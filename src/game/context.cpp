//
// Created by malo1 on 5/27/2024.
//

#include <iostream>

#include <SDL2/SDL.h>

#include "context.h"

context::context(unsigned int _width, unsigned int _height)
    : width(_width), height(_height), window(nullptr), renderer(nullptr)
{
    if(auto code = SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error on SDL_Init with code " << code << " : " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Jeu ESIR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_RESIZABLE);
    if(!window) {
        std::cerr << "Error on SDL_CreateWindow : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::cerr << "Error on SDL_CreateRenderer : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

context::~context() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
