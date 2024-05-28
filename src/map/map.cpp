//
// Created by tomch on 28/05/2024.
//
#include <array>
#include <fstream>
#include <iostream>

#include <cstring>
#include <cassert>

#include "map.h"
#include "entity/entity.h"

map::map(unsigned int _width, unsigned int _height) {
    float cw = config::map::cluster_width;
    float ch = config::map::cluster_height;
}

struct csv_line {
    enum class entity_type {
        tile,
    } type;
    float x, y;
};

csv_line read_csv_line(const char* line) {
    char* after;

    assert('0' == line[0] && "J'ai super envie de mourrir <-- oui j'ai mis deux r et je vois pas le problEME !!!!!!");

    // le premier charactère est 0 suivis d'un espace simple
    line += 2;

    double x = std::strtod(line, &after);
    if(line == after) {
        std::cerr << "could not read x position, currently at : " << line << std::endl;
    }
    line = after;

    double y = std::strtod(line, &after);
    if(after == line) {
        std::cerr << "could not read y position, currently at : " << line << std::endl;
    }

    return csv_line {
            csv_line::entity_type::tile,
            static_cast<float>(x), static_cast<float>(y)
    };
}

void map::load_wsv(vec2<float> size, const char * file){
    std::ifstream input_file(file);

    constexpr uint16_t cw = config::map::cluster_width;
    constexpr uint16_t ch = config::map::cluster_height;

    char buffer[2048] = { 0 };
    input_file.getline(buffer, 2048);

    char *start = buffer, *after = start;

    // read width
    unsigned long width = strtoul(start, &after, 10);
    if(after == start) {
        std::cerr << "could not read width, currently at : " << start << std::endl;
    }
    start = after;

    // read height
    unsigned long height = strtoul(start, &after, 10);
    if(after == start) {
        std::cerr << "could not read height, currently at : " << start << std::endl;
    }

    this->nb_clusters_x = std::ceil(width/cw);
    this->nb_clusters_y = std::ceil(height/ch);
    for(unsigned int x = 0; x < this->nb_clusters_x ; x++) {
        for(unsigned int y = 0 ; y < this->nb_clusters_y ; y++) {
            this->clusters.push_back(cluster({static_cast<float>(y*ch),static_cast<float>((x+1)*cw),static_cast<float>((y+1)*ch),static_cast<float>(x*cw)}));
        }
    }

    for (; input_file.getline(buffer, 2048); ) {
        csv_line line = read_csv_line(buffer);
        switch (line.type) {
            case csv_line::entity_type::tile: {
                unsigned int idx = this->find_cluster_idx({{line.x, line.y}});
                // this->clusters[idx].background.push_back(new entity(line.x, line.y, config::map::tile_width, config::map::tile_height))
            } break;
            default: {
                std::cerr << "unknown entity type in map !" << std::endl;
            } break;
        }
    }
}

void map::draw() {

}

void map::update() {

}

// protected utilities

uint32_t map::find_cluster_idx(const vec2<float>& position) const {
    return ((int)position.y/config::map::cluster_height)*this->nb_clusters_x + ((int)position.x/config::map::cluster_width);
}

std::vector<cluster*> map::get_surrounding_clusters(uint32_t cluster_idx) {
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

std::vector<cluster const*> map::get_cluster_to_blit(const camera & camera) const {

    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = find_cluster_idx({camera.get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = find_cluster_idx({camera.get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx-top_left_cluster_idx)/this->nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx-top_left_cluster_idx)%this->nb_clusters_x;

    std::vector<cluster const*> res(dx*dy);
    for(uint32_t i = 0 ; i < dx ; i++) {
        for(uint32_t j = 0 ; j < dy ; j++) {
            uint32_t idx = top_left_cluster_idx + i * this->nb_clusters_x + j;
            res.push_back(&clusters[idx]);
        }
    }
    return res;
}
