//
// Created by viann on 28/05/2024.
//
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <cassert>

#include "utils/vec2.h"
#include "texture_manager.h"

namespace serializer {

    struct map_header {
        uint32_t width, height;
    };

    struct map_row {
        enum class entity_type : uint32_t {
            tile,
            animated_tile,
            player,

            count,
        } type;

        vec2<float> position;

        union {
            struct {
                uint32_t i, j;
                texture_manager::atlases atlas_id;
            } tile;

            struct {
                uint32_t animation_id;
            } animated_tile;

            struct {} player;
        };
    };

    std::istream& operator>>(std::istream& is, map_row::entity_type& type);

    struct map {
        map_header header;
        std::vector<map_row> data;
    };

    map deserialize(const char* filepath);

} // namespace serializer
