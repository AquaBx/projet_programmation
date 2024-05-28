//
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"

 game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), m(0, 0), p(new player({{0.f, 100.f}}, {{48.f, 48.f}}, 100))
{
    ui_components.push_back(new health_bar(p, 220, 20, 41, 7));
}

game::~game() {
    delete p;
    for (auto component : ui_components) delete component;
}

void game::run() {

    while(running) {
        event::manager::update();

        p->update(0.1);
//        for (auto component : ui_components) {
//            component->update(0.1);
//        }

        renderer::clear(0, 0, 0);

        p->draw();

//        for (auto component : ui_components) {
//            component->draw();
//        }

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

/*
interactible * game::perceive(const player * user){
    interactible * nearest = nullptr;
    float nearest_dist = 0;

    for(cluster* c : get_surrounding_clusters(find_cluster_idx(user->get_position()))) {
        for (interactible * objet : c->interactibles){
            const float shared_dist = physics::shared_distance(user->get_interact_zone() , objet->get_interact_zone());

            if( shared_dist > nearest_dist ) {
                nearest = objet;
                nearest_dist = shared_dist;
            }
        }
    }

    return nearest;
}
*/
