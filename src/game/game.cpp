//
// Created by malo1 on 5/27/2024.
//
#include "game.h"
#include "renderer.h"
#include "event.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), p(new player(0, 0, 5, 5)) {}

game::~game() {
    delete p;
}

void game::run() {
    while(running) {
        event::manager::update();

        p->update(0.1);
        renderer::clear(0, 0, 0);
        p->draw();
        renderer::present();
    }
}

void game::handle_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EventType::SDL_QUIT: {
            running = false;
        } break;
    }
}
