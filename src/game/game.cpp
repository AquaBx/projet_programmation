 //
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include <iostream>

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"
#include "config.h"
#include "sprites/sprite.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), p(new player(0, 0, 5, 5, 100, 5))

{
    ui_components.push_back(new health_bar(p, 220, 20, 41, 7));

    float cw = config::map::cluster_width;
    float ch = config::map::cluster_height;
    // ça devrait se baser sur la map, pas sur la fenetre de jeu
    this->nb_clusters_x = std::ceil(_width/cw);
    this->nb_clusters_y = std::ceil(_height/ch);
    for(unsigned int x = 0; x < this->nb_clusters_x ; x++) {
        for(unsigned int y = 0 ; y < this->nb_clusters_y ; y++) {
            this->clusters.push_back(cluster({y*ch,(x+1)*cw,(y+1)*ch,x*cw}));
        }
    }
    //might be worth storing it inside entity
    unsigned int player_cluster_idx = find_cluster_idx(p->get_position());
    clusters[player_cluster_idx].entities.insert(p);
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

uint32_t game::find_cluster_idx(const vec2<float>& position) const {
    return ((int)position.y/config::map::cluster_height)*this->nb_clusters_x + ((int)position.x/config::map::cluster_width);
}

std::vector<cluster*> game::get_surrounding_clusters(uint32_t cluster_idx) {
    std::vector<cluster*> res;
    for(int i = -1 ; i < 2 ; i++) {
        for(int j = -1 ; j < 2 ; j++) {
            uint32_t idx = cluster_idx + i * this->nb_clusters_x + j;
            // assuming negatives values aren't to negatives, could use boolean logic in for boundaries instead
            if(idx < this->nb_clusters_x * this->nb_clusters_y)
                res.push_back(&clusters[idx]);
        }
    }
    return res;
}

std::vector<cluster *> game::get_cluster_to_blit(camera *camera) {

    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = find_cluster_idx({camera->get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = find_cluster_idx({camera->get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx-top_left_cluster_idx)/this->nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx-top_left_cluster_idx)%this->nb_clusters_x;

    std::vector<cluster*> res(dx*dy);
    for(uint32_t i = 0 ; i < dx ; i++) {
        for(uint32_t j = 0 ; j < dy ; j++) {
            uint32_t idx = top_left_cluster_idx + i * this->nb_clusters_x + j;
            res.emplace_back(&clusters[idx]);
        }
    }
    return res;
}
