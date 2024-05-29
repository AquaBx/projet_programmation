//
// Created by malo1 on 5/27/2024.
//
#pragma once

#include <cstdint>

namespace config {

    constexpr float tick_time = 1.f / 30.f;

    namespace viewport {

        constexpr uint16_t width = 240;
        constexpr uint16_t height = 135;

    } // namespace viewport

    namespace window {

        constexpr uint16_t width = 480;
        constexpr uint16_t height = 270;

    } // namespace window

    constexpr struct {
        float x = static_cast<float>(config::window::width) / static_cast<float>(config::viewport::width);
        float y = static_cast<float>(config::window::height) / static_cast<float>(config::viewport::height);
    } ratio;

    namespace map {

        constexpr uint16_t cluster_width = 50;
        constexpr uint16_t cluster_height = 50;

        constexpr float tile_width = 16;
        constexpr float tile_height = 16;

    } // namespace map

    namespace serializer {

        constexpr char prelude[] = "MAPV1";

    } // namespace serializer

} // namespace config
