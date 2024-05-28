//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <cstdint>

namespace config {

    namespace window {

        constexpr uint16_t width = 440;
        constexpr uint16_t height = 608;

    } // namespace window

    namespace map {

        constexpr uint16_t cluster_width = 50;
        constexpr uint16_t cluster_height = 50;

        constexpr float tile_width = 16;
        constexpr float tile_height = 16;

    } // namespace map

} // namespace config
