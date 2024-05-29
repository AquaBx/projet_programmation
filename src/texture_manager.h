//
// Created by malo1 on 5/28/2024.
//
#pragma once

#include <cassert>

#include <array>
#include <string>
#include <fstream>
#include <unordered_map>

#include <SDL2/SDL_render.h>

namespace texture_manager {

    enum class atlases : uint32_t {
        tilemap,

        count,
    };

    extern std::array<std::string, (size_t)atlases::count> atlases_name;
    extern std::unordered_map<std::string, SDL_Texture*> loaded_textures;

    std::ifstream& operator>>(std::ifstream& is, atlases& a);
    void initialize_atlases();
    void terminate();

} // namespace texture_manager
