//
// Created by malo1 on 5/27/2024.
//
#include <iostream>
#include "game.h"

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"

std::vector<gui_component *> game::ui_components;


game::game(unsigned int _width, unsigned int _height)
        : context(_width, _height), previous_tick(SDL_GetTicks()) {
    map::load("../resources/map.map");
    // ui_components.push_back(new health_bar(m.player, 220, 20, 41, 7));
}

game::~game() {
    for (auto component: ui_components) delete component;
}

void game::run() {

    while (running) {
        uint32_t start_tick = SDL_GetTicks();
        float dt = static_cast<float>(static_cast<double>(start_tick - previous_tick) / 1000.0);

        event::manager::update();
        map::update(dt);
        for (auto component: ui_components) {
            component->update(dt);
        }

        /* Render Pass */
        renderer::clear(0, 0, 0);
        map::draw();
        for (auto component: ui_components) {
            component->draw(map::cam);
        }
        // menus

        renderer::present();

        previous_tick = start_tick;
        if (config::tick_time > dt) SDL_Delay((uint32_t) (config::tick_time - dt) * 1000);
        else std::cout << "can't keep it up (" << dt - config::tick_time << " seconds behind)\n";
    }
}

void game::handle_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EventType::SDL_QUIT: {
            running = false;
        }
            break;
    }
}