 //
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include <iostream>

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"

#include "sprites/sprite.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), p(new player(0, 0, 5, 5, 100))
{
    ui_components.push_back(new health_bar(p, 220, 20, 41, 7));
}

game::~game() {
    delete p;
    for (auto component : ui_components) delete component;
}

void game::run() {
    vec2<float> position;
    position.x=0;
    position.y=0;

    vec2<int> resolution;
    resolution.width=48;
    resolution.height=48;

     vec2<float> size;
    size.width=100;
    size.height=100;

    std::vector<int> max_frames;
    max_frames.push_back(4);

    sprite test(position,size,resolution,max_frames);

     int a = test.load_texture("../resources/test.bmp");
     std::cout<<a;

    while(running) {
        event::manager::update();

        p->update(0.1);

        test.update(0.1);

        for (auto component : ui_components) {
            component->update(0.1);
        }

        renderer::clear(0, 0, 0);

        p->draw();

        test.draw();

        for (auto component : ui_components) {
            component->draw();
        }

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
