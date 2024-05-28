//
// Created by tomch on 28/05/2024.
//

#pragma once

#include "config.h"
#include "utils/vec2.h"
#include "cluster.h"
#include "camera.h"
#include <vector>

class map {

public:
    map(unsigned int _width, unsigned int _height);

    void load_wsv(vec2<float> size, const char * file);

    void draw();
    void update();

protected:
    unsigned int find_cluster_idx(const vec2<float>& position) const;
    std::vector<cluster*> get_surrounding_clusters(unsigned int cluster_idx);
    std::vector<cluster const*> get_cluster_to_blit(const camera & camera) const;

protected:
    std::vector<cluster> clusters;
    unsigned int nb_clusters_x, nb_clusters_y;
};