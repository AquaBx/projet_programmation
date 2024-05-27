//
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include "color.h"
#include "renderer.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height)
{}

void game::run() {

    while(true) {
        renderer::clear(0, 0, 0);
        renderer::draw_rect(0, 0, 50, 50, renderer::colors::red);
        renderer::present();
    }

}
