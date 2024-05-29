//
// Created by tomch on 28/05/2024.
//

#include <iostream>

#include <vector>

#include "map.h"
#include "config.h"
#include "cluster.h"
#include "entity/entity.h"
#include "entity/cow.h"
#include "entity/fusee.h"
#include "entity/tomato_crop.h"
#include "entity/wheat_crop.h"
#include "game/game.h"

#include "serializer.h"
#include "entity/chicken.h"
#include "entity/copper.h"
#include "GUI/copper_bar.h"

camera map::cam;
player *map::p;
uint32_t map::map_tick = 0;

std::vector<cluster> map::clusters;
static unsigned int nb_clusters_x, nb_clusters_y;

static std::vector<cluster const*> get_cluster_to_blit(const camera& camera);

void map::load(const char *file) {
    serializer::map data = serializer::deserialize(file);

    constexpr uint16_t cw = config::map::cluster_width;
    constexpr uint16_t ch = config::map::cluster_height;

    // TODO BIG BIG BIG MEMORY LEAK
    clusters.clear();

    nb_clusters_x = std::ceil((float) data.header.width / cw);
    nb_clusters_y = std::ceil((float) data.header.height / ch);
    for (unsigned int y = 0; y < nb_clusters_y; y++) {
        for (unsigned int x = 0; x < nb_clusters_x; x++) {
            clusters.push_back(cluster({
                                               static_cast<float>(y * ch),
                                               static_cast<float>((x + 1) * cw),
                                               static_cast<float>((y + 1) * ch),
                                               static_cast<float>(x * cw)
                                       }));
        }
    }


    for (serializer::map_row &row: data.data) {
        uint32_t idx = find_cluster_idx(row.position);
        switch (row.type) {
            case serializer::map_row::entity_type::tile: {
                clusters[idx].background.push_back(
                        new sprite(
                                row.position,
                                {{config::map::tile_width, config::map::tile_height}}, // ce que l'on veut afficher
                                {{row.tile.i, row.tile.j}},
                                {{16, 16}}, // ce qu'on lit dans le fichier
                                {{config::map::tile_width / 2, config::map::tile_height / 2}},
                                texture_manager::atlases_name[(size_t) row.tile.atlas_id].c_str()
                        )
                );
            }
                break;

            case serializer::map_row::entity_type::animated_tile: {
                // clusters[idx].background.push_back();
                std::cerr << "Not implemented yet !" << std::endl;
            }
                break;

            case serializer::map_row::entity_type::player: {
                // init player
                p = new player(row.position, {{48.0f, 48.0f}}, 100, 100, 100);
                health_bar *h = new health_bar({{10, config::window::height - 25}}, {{123, 21}}, {0, 2}, {89, 16},
                                               "../resources/bars.png", p);
                game::ui_components.push_back(h);
                game::ui_components.push_back(new food_bar({{10, config::window::height - 50}}, {{123, 21}}, {0, 1},
                                                           {{89, 16}}, "../resources/bars.png", p));

                game::ui_components.push_back(h);
                game::ui_components.push_back(new copper_bar({{10, config::window::height - 75}}, {{123, 21}}, {0, 0},
                                                           {{89, 16}}, "../resources/bars.png", p));


                clusters[idx].foreground.insert(p);
                float offset_x = row.position.x - static_cast<float>(config::viewport::width) / 2.0f, offset_y = row.
                        position.y -
                                                                                                                 static_cast<float>(config::viewport::height) /
                                                                                                                 2.0f;
                cam = camera({{offset_x, offset_y}}, {
                        {
                                static_cast<float>(config::viewport::width),
                                static_cast<float>(config::viewport::height)
                        }
                }, .8f, 2.f, p);
            }
                break;
            case serializer::map_row::entity_type::cow: {
                // init cow
                cow *m_cow = new cow(row.position, {{32.0f, 32.0f}}, 100);

                clusters[idx].foreground.insert(m_cow);
                clusters[idx].collidables.insert(m_cow);
                clusters[idx].interactibles.insert(m_cow);
            }
                break;

            case serializer::map_row::entity_type::chicken: {
                // init cow
                chicken *m_chicken = new chicken(row.position, {{16.0f, 16.0f}}, 100);

                clusters[idx].foreground.insert(m_chicken);
                clusters[idx].collidables.insert(m_chicken);
                clusters[idx].interactibles.insert(m_chicken);
            }
                break;

            case serializer::map_row::entity_type::fusee: {
                // init fusee
                fusee *m_cow = new fusee(row.position, {{48.0f, 48.0f}}, 50);

                clusters[idx].foreground.insert(m_cow);
                clusters[idx].collidables.insert(m_cow);
                clusters[idx].interactibles.insert(m_cow);
            }
                break;

            case serializer::map_row::entity_type::wheat: {
                // init wheat
                wheat_crop *m_wheat = new wheat_crop(row.position, {{16.0f, 16.0f}});

                clusters[idx].foreground.insert(m_wheat);
                clusters[idx].interactibles.insert(m_wheat);
            }
                break;

            case serializer::map_row::entity_type::copper: {
                // init wheat
                copper *m_copper = new copper(row.position, {{16.0f, 16.0f}});

                clusters[idx].foreground.insert(m_copper);
                clusters[idx].interactibles.insert(m_copper);
            }
            break;

            case serializer::map_row::entity_type::tomato: {
                // init tomato
                tomato_crop *m_tomato = new tomato_crop(row.position, {{16.0f, 16.0f}});

                clusters[idx].foreground.insert(m_tomato);
                clusters[idx].interactibles.insert(m_tomato);
            }
                break;
            default: {
                std::cerr << "unknown entity type in map !" << std::endl;
            }
                break;
        }
    }

}

void map::draw() {
    std::vector<const cluster *> cs = get_cluster_to_blit(cam);
    for (const cluster *c: cs) {
        for (sprite *e: c->background) {
            e->draw(cam);
        }
    }

    std::set<sprite *, y_sort> all_to_blit;
    for (const cluster *c: cs) {
        for (sprite *e: c->foreground) {
            all_to_blit.insert(e);
        }
    }
    for (sprite *e: all_to_blit) e->draw(cam);
}

void map::update(float dt) {
    map::map_tick = SDL_GetTicks();
    std::vector<const cluster *> cs = get_cluster_to_blit(cam);
    for (const cluster *c: cs) {
        for (sprite *e: c->background) {
            e->update(dt);
        }

        auto foreground_copy(c->foreground);
        for (sprite *e: foreground_copy) {
            e->update(dt);
        }
    }
    cam.update();
}

// protected utilities

uint32_t map::find_cluster_idx(const vec2<float> &position) {
    return ((int) position.y / config::map::cluster_height) * nb_clusters_x + ((int) position.x /
                                                                               config::map::cluster_width);
}

std::vector<cluster *> map::get_surrounding_clusters(uint32_t cluster_idx) {
    std::vector<cluster *> res;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            uint32_t idx = cluster_idx + i * nb_clusters_x + j;
            // assuming negatives values aren't to negatives, could use boolean logic in for boundaries instead
            if (idx < nb_clusters_x * nb_clusters_y)
                res.push_back(&map::clusters[idx]);
        }
    }
    return res;
}

std::vector<cluster const *> get_cluster_to_blit(const camera &camera) {
    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = map::find_cluster_idx({camera.get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = map::find_cluster_idx({camera.get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx - top_left_cluster_idx) % nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx - top_left_cluster_idx) / nb_clusters_x;

    std::vector<cluster const *> res;
    for (uint32_t i = 0; i < dy; i++) {
        for (uint32_t j = 0; j < dx; j++) {
            uint32_t idx = top_left_cluster_idx + i * nb_clusters_x + j;
            res.emplace_back(&map::clusters[idx]);
        }
    }
    return res;
}

interactible *map::perceive(player *user, const std::vector<cluster *> &cs) {
    interactible *nearest = nullptr;
    float nearest_dist = 0.0f;

    for (cluster *c: cs) {
        for (interactible *objet: c->interactibles) {
            const float shared_dist = physics::shared_distance(user->get_interact_zone(), objet->get_interact_zone());

            if (shared_dist > nearest_dist) {
                nearest = objet;
                nearest_dist = shared_dist;
            }
        }
    }

    return nearest;
}
