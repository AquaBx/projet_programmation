//
// Created by malo1 on 5/27/2024.
//

#include "game.h"

game::game(unsigned int _width, unsigned int _height) : context(_width, _height) {}

void game::run() {
    gameLoop();
}

void game::gameLoop() {
    while(true) {
        SDL_Rect rect{0,0,50,50};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }
}
