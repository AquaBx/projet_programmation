//
// Created by viann on 27/05/2024.
//
#pragma once

#include <cstdint>

namespace renderer {

    struct color {
        uint8_t r, g, b, a;
    };

    namespace colors {

        constexpr color white = {255, 255, 255, 255};
        constexpr color black = {0, 0, 0, 255};

        constexpr color red = {255, 0, 0, 255};
        constexpr color green = {0, 255, 0, 255};
        constexpr color blue = {0, 0, 255, 255};

        constexpr color beige = {237, 211, 171, 255};

    } // namespace colors

} // namespace renderer
